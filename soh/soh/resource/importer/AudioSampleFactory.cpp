#include "soh/resource/importer/AudioSampleFactory.h"
#include "soh/resource/type/AudioSample.h"
#include "soh/resource/importer/AudioSoundFontFactory.h"
#include "StringHelper.h"
#include "libultraship/libultraship.h"
#include "z64audio.h"
#define DR_WAV_IMPLEMENTATION
#include <dr_wav.h>

#define DR_MP3_IMPLEMENTATION
#include <dr_mp3.h>

#define DR_FLAC_IMPLEMENTATION
#include <dr_flac.h>

#include "vorbis/vorbisfile.h"
#include <tinyxml2.h>

struct OggFileData {
    void* data;
    size_t pos;
    size_t size;
};

static size_t VorbisReadCallback(void* out, size_t size, size_t elems, void* src) {
    OggFileData* data = static_cast<OggFileData*>(src);
    size_t toRead = size * elems;

    if (toRead > data->size - data->pos) {
        toRead = data->size - data->pos;
    }

    memcpy(out, static_cast<uint8_t*>(data->data) + data->pos, toRead);
    data->pos += toRead;

    return toRead / size;
}

static int VorbisSeekCallback(void* src, ogg_int64_t pos, int whence) {
    OggFileData* data = static_cast<OggFileData*>(src);
    size_t newPos;

    switch (whence) {
        case SEEK_SET:
            newPos = pos;
            break;
        case SEEK_CUR:
            newPos = data->pos + pos;
            break;
        case SEEK_END:
            newPos = data->size + pos;
            break;
        default:
            return -1;
    }
    if (newPos > data->size) {
        return -1;
    }
    data->pos = newPos;
    return 0;
}

static int VorbisCloseCallback([[maybe_unused]] void* src) {
    return 0;
}

static long VorbisTellCallback(void* src) {
    OggFileData* data = static_cast<OggFileData*>(src);
    return data->pos;
}

static const ov_callbacks vorbisCallbacks = {
    VorbisReadCallback,
    VorbisSeekCallback,
    VorbisCloseCallback,
    VorbisTellCallback,
};

static void Mp3DecoderWorker(std::shared_ptr<SOH::AudioSample> audioSample, std::shared_ptr<Ship::File> sampleFile) {
    drmp3 mp3;
    drwav_uint64 numFrames;
    drmp3_bool32 ret =
        drmp3_init_memory(&mp3, sampleFile->Buffer.get()->data(), sampleFile->Buffer.get()->size(), nullptr);
    numFrames = drmp3_get_pcm_frame_count(&mp3);
    drwav_uint64 channels = mp3.channels;
    drwav_uint64 sampleRate = mp3.sampleRate;

    audioSample->sample.sampleAddr = new uint8_t[numFrames * channels * 2];
    drmp3_read_pcm_frames_s16(&mp3, numFrames, (int16_t*)audioSample->sample.sampleAddr);
}

static void FlacDecoderWorker(std::shared_ptr<SOH::AudioSample> audioSample, std::shared_ptr<Ship::File> sampleFile) {
    drflac* flac = drflac_open_memory(sampleFile->Buffer.get()->data(), sampleFile->Buffer.get()->size(), nullptr);
    drflac_uint64 numFrames = flac->totalPCMFrameCount;
    audioSample->sample.sampleAddr = new uint8_t[numFrames * flac->channels * 2];
    drflac_read_pcm_frames_s16(flac, numFrames, (int16_t*)audioSample->sample.sampleAddr);
    drflac_close(flac);
}

static void OggDecoderWorker(std::shared_ptr<SOH::AudioSample> audioSample, std::shared_ptr<Ship::File> sampleFile) {
    OggVorbis_File vf;
    char dataBuff[4096];
    long read = 0;
    size_t pos = 0;

    OggFileData fileData = {
        .data = sampleFile->Buffer.get()->data(),
        .pos = 0,
        .size = sampleFile->Buffer.get()->size(),
    };
    int ret = ov_open_callbacks(&fileData, &vf, nullptr, 0, vorbisCallbacks);

    vorbis_info* vi = ov_info(&vf, -1);

    uint64_t numFrames = ov_pcm_total(&vf, -1);
    uint64_t sampleRate = vi->rate;
    uint64_t numChannels = vi->channels;
    int bitStream = 0;
    size_t toRead = numFrames * numChannels * 2;
    audioSample->sample.sampleAddr = new uint8_t[toRead];
    do {
        read = ov_read(&vf, dataBuff, 4096, 0, 2, 1, &bitStream);
        memcpy(audioSample->sample.sampleAddr + pos, dataBuff, read);
        pos += read;
    } while (read != 0);
    ov_clear(&vf);
}

namespace SOH {
std::shared_ptr<Ship::IResource> ResourceFactoryBinaryAudioSampleV2::ReadResource(std::shared_ptr<Ship::File> file, std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto audioSample = std::make_shared<AudioSample>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    audioSample->sample.codec = reader->ReadUByte();
    audioSample->sample.medium = reader->ReadUByte();
    audioSample->sample.unk_bit26 = reader->ReadUByte();
    audioSample->sample.unk_bit25 = reader->ReadUByte();
    audioSample->sample.size = reader->ReadUInt32();

    audioSample->sample.sampleAddr = new uint8_t[audioSample->sample.size];
    for (uint32_t i = 0; i < audioSample->sample.size; i++) {
        audioSample->sample.sampleAddr[i] = reader->ReadUByte();
    }

    audioSample->loop.start = reader->ReadUInt32();
    audioSample->loop.end = reader->ReadUInt32();
    audioSample->loop.count = reader->ReadUInt32();

    // This always seems to be 16. Can it be removed in V3?
    uint32_t loopStateCount = reader->ReadUInt32();
    for (int i = 0; i < 16; i++) {
        audioSample->loop.state[i] = 0;
    }
    for (uint32_t i = 0; i < loopStateCount; i++) {
        audioSample->loop.state[i] = reader->ReadInt16();
    }
    audioSample->sample.loop = &audioSample->loop;

    audioSample->book.order = reader->ReadInt32();
    audioSample->book.npredictors = reader->ReadInt32();
    uint32_t bookDataCount = reader->ReadUInt32();

    audioSample->book.book = new int16_t[bookDataCount];

    for (uint32_t i = 0; i < bookDataCount; i++) {
        audioSample->book.book[i] = reader->ReadInt16();
    }
    audioSample->sample.book = &audioSample->book;

    return audioSample;
}

std::shared_ptr<Ship::IResource> ResourceFactoryXMLAudioSampleV0::ReadResource(std::shared_ptr<Ship::File> file, std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto audioSample = std::make_shared<AudioSample>(initData);
    auto child = std::get<std::shared_ptr<tinyxml2::XMLDocument>>(file->Reader)->FirstChildElement();
    std::shared_ptr<Ship::ResourceInitData> initDataToLoad = std::make_shared<Ship::ResourceInitData>();
    const char* customFormatStr = child->Attribute("CustomFormat");
    memset(&audioSample->sample, 0, sizeof(audioSample->sample));
    audioSample->sample.unk_bit25 = 0;
    audioSample->sample.codec = CodecStrToInt(child->Attribute("Codec"));
    audioSample->sample.medium = ResourceFactoryXMLSoundFontV0::MediumStrToInt(child->Attribute("Medium"));
    audioSample->sample.unk_bit26 = child->IntAttribute("bit26");

    tinyxml2::XMLElement* loopRoot = child->FirstChildElement("ADPCMLoop");
    if (loopRoot != nullptr) {
        size_t i = 0;
        audioSample->loop.start = loopRoot->UnsignedAttribute("Start");
        audioSample->loop.end = loopRoot->UnsignedAttribute("End");
        audioSample->loop.count = loopRoot->UnsignedAttribute("Count");
        tinyxml2::XMLElement* predictor = loopRoot->FirstChildElement("Predictor");
        while (predictor != nullptr) {
            audioSample->loop.state[i++] = predictor->IntAttribute("State");
            predictor = predictor->NextSiblingElement();
        }
    }

    tinyxml2::XMLElement* bookRoot = child->FirstChildElement("ADPCMBook");
    if (bookRoot != nullptr) {
        size_t i = 0;
        audioSample->book.npredictors = bookRoot->IntAttribute("Npredictors");
        audioSample->book.order = bookRoot->IntAttribute("Order");
        tinyxml2::XMLElement* book = bookRoot->FirstChildElement("Book");
        size_t numBooks = audioSample->book.npredictors * audioSample->book.order * 8;
        audioSample->book.book = new int16_t[numBooks];
        while (book != nullptr) {
            audioSample->book.book[i++] = book->IntAttribute("Page");
            book = book->NextSiblingElement();
        }
        audioSample->sample.book = &audioSample->book;
    }

    audioSample->sample.loop = &audioSample->loop;
    size_t size = child->Int64Attribute("Size");
    audioSample->sample.size = size;

    const char* path = child->Attribute("Path");
    initDataToLoad->Path = path;
    initDataToLoad->IsCustom = false;
    initDataToLoad->ByteOrder = Ship::Endianness::Native;
    auto sampleFile = Ship::Context::GetInstance()->GetResourceManager()->GetArchiveManager()->LoadFile(path);
    if (customFormatStr != nullptr) {
        // Compressed files can take a really long time to decode (~250ms per).
        // This worked when we tested it (09/04/2024) (Works on my machine)
        if (strcmp(customFormatStr, "wav") == 0) {
            drwav wav;
            drwav_uint64 numFrames;

            drwav_bool32 ret =
                drwav_init_memory(&wav, sampleFile->Buffer.get()->data(), sampleFile->Buffer.get()->size(), nullptr);

            drwav_get_length_in_pcm_frames(&wav, &numFrames);

            audioSample->tuning = (wav.sampleRate * wav.channels) / 32000.0f;
            audioSample->sample.sampleAddr = new uint8_t[numFrames * wav.channels * 2];

            drwav_read_pcm_frames_s16(&wav, numFrames, (int16_t*)audioSample->sample.sampleAddr);
            return audioSample;
        } else if (strcmp(customFormatStr, "mp3") == 0) {
            std::thread fileDecoderThread = std::thread(Mp3DecoderWorker, audioSample, sampleFile);
            fileDecoderThread.detach();
            return audioSample;
        } else if (strcmp(customFormatStr, "ogg") == 0) {
            std::thread fileDecoderThread = std::thread(OggDecoderWorker, audioSample, sampleFile);
            fileDecoderThread.detach();
            return audioSample;
        } else if (strcmp(customFormatStr, "flac") == 0) {
            std::thread fileDecoderThread = std::thread(FlacDecoderWorker, audioSample, sampleFile);
            fileDecoderThread.detach();
            return audioSample;
        }
    }
    // Not a normal streamed sample. Fallback to the original ADPCM sample to be decoded by the audio engine.
    audioSample->sample.sampleAddr = new uint8_t[size];
    // Can't use memcpy due to endianness issues.
    for (uint32_t i = 0; i < size; i++) {
        audioSample->sample.sampleAddr[i] = sampleFile->Buffer.get()->data()[i];
    }

    return audioSample;
}
#include <cassert>
uint8_t ResourceFactoryXMLAudioSampleV0::CodecStrToInt(const char* str) {
    if (strcmp("ADPCM", str) == 0) {
        return CODEC_ADPCM;
    } else if (strcmp("S8", str) == 0) {
        return CODEC_S8;
    } else if (strcmp("S16MEM", str) == 0) {
        return CODEC_S16_INMEMORY;
    } else if (strcmp("ADPCMSMALL", str) == 0) {
        return CODEC_SMALL_ADPCM;
    } else if (strcmp("REVERB", str) == 0) {
        return CODEC_REVERB;
    } else if (strcmp("S16", str) == 0) {
        return CODEC_S16;
    } else {
        assert(0);
    }
}
} // namespace SOH
