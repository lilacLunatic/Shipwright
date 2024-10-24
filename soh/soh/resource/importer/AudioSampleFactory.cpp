#include "soh/resource/importer/AudioSampleFactory.h"
#include "soh/resource/type/AudioSample.h"
#include "spdlog/spdlog.h"
#define DRMP3_IMPLEMENTATION
#include <dr_libs/mp3.h>
#define DRWAV_IMPLEMENTATION
#include <dr_libs/wav.h>
#define DRFLAC_IMPLEMENTATION
#include <dr_libs/flac.h>

#define AUDIO_SAMPLE_VERSION_0 0x00
#define AUDIO_SAMPLE_VERSION_2 0x02
#define CUSTOM_AUDIO_SAMPLE_VERSION_0 0xC0

namespace SOH {
std::shared_ptr<Ship::IResource> ResourceFactoryBinaryAudioSampleV2::ReadResource(std::shared_ptr<Ship::File> file) {
    if (!FileHasValidFormatAndReader(file)) {
        return nullptr;
    }
    auto audioSample = std::make_shared<AudioSample>(file->InitData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    audioSample->sample.codec = reader->ReadUByte();
    audioSample->sample.medium = reader->ReadUByte();
    audioSample->sample.unk_bit26 = reader->ReadUByte();
    audioSample->sample.unk_bit25 = reader->ReadUByte();
    audioSample->sample.size = reader->ReadUInt32();

    audioSample->audioSampleData.reserve(audioSample->sample.size);
    for (uint32_t i = 0; i < audioSample->sample.size; i++) {
        audioSample->audioSampleData.push_back(reader->ReadUByte());
    }
    audioSample->sample.sampleAddr = audioSample->audioSampleData.data();

    audioSample->loop.start = reader->ReadUInt32();
    audioSample->loop.end = reader->ReadUInt32();
    audioSample->loop.count = reader->ReadUInt32();

    audioSample->loopStateCount = reader->ReadUInt32();
    for (int i = 0; i < 16; i++) {
        audioSample->loop.state[i] = 0;
    }
    for (uint32_t i = 0; i < audioSample->loopStateCount; i++) {
        audioSample->loop.state[i] = reader->ReadInt16();
    }
    audioSample->sample.loop = &audioSample->loop;

    audioSample->book.order = reader->ReadInt32();
    audioSample->book.npredictors = reader->ReadInt32();
    audioSample->bookDataCount = reader->ReadUInt32();

    audioSample->bookData.reserve(audioSample->bookDataCount);
    for (uint32_t i = 0; i < audioSample->bookDataCount; i++) {
        audioSample->bookData.push_back(reader->ReadInt16());
    }
    audioSample->book.book = audioSample->bookData.data();
    audioSample->sample.book = &audioSample->book;

    return audioSample;

}
std::shared_ptr<Ship::IResource> ResourceFactoryBinaryCustomAudioSampleV0::ReadResource(std::shared_ptr<Ship::File> file) {
    if (!FileHasValidFormatAndReader(file)) {
        return nullptr;
    }
    auto audioSample = std::make_shared<AudioSample>(file->InitData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);
    auto format = static_cast<AudioFormat>(reader->ReadUByte());

    const auto pitch = reader->ReadFloat();
    const auto length = reader->ReadUInt32();
    const auto bytes = new uint8_t[length];
    reader->Read(reinterpret_cast<char*>(bytes), static_cast<int32_t>(length));

    switch (format) {
        case AudioFormat::WAV: {
            drwav wav;
            bool hasLoop = false;
            drwav_init_memory_with_metadata(&wav, bytes, length, 0, nullptr);

            if(wav.pMetadata != nullptr) {
                for(size_t id = 0; id < wav.metadataCount; id++) {
                    const auto metadata = wav.pMetadata[id];

                    if(metadata.type == drwav_metadata_type_smpl) {
                        const auto smpl = wav.pMetadata->data.smpl;
                        if(smpl.sampleLoopCount > 0) {
                            audioSample->loop.start = smpl.pLoops[0].firstSampleByteOffset;
                            audioSample->loop.end = smpl.pLoops[0].lastSampleByteOffset;
                            audioSample->loop.count = 1;
                            audioSample->loopStateCount = 1;
                            hasLoop = true;
                            break;
                        }
                    }
                }
            }

            if(!hasLoop) {
                audioSample->loop.count = 0;
                audioSample->loop.start = 0;
                audioSample->loop.end = wav.totalPCMFrameCount;
            }

            const auto pcmData = drwav__read_pcm_frames_and_close_s16(&wav, nullptr, nullptr, nullptr);

            audioSample->sample.size = wav.totalPCMFrameCount * wav.channels * sizeof(int16_t);
            audioSample->sample.sampleAddr = reinterpret_cast<uint8_t *>(pcmData);
            audioSample->sample.codec = CODEC_S16;
            audioSample->sample.sampleRateMagicValue = 'RIFF';
            audioSample->sample.sampleRate = wav.sampleRate * pitch;
            audioSample->sample.loop = &audioSample->loop;
            break;
        }
        case AudioFormat::MP3: {
            drmp3_config mp3Info;
            drmp3_uint64 totalPcm;
            drmp3_int16* pcmData = drmp3_open_memory_and_read_pcm_frames_s16(bytes, length, &mp3Info, &totalPcm, nullptr);

            audioSample->sample.size = totalPcm * mp3Info.channels * sizeof(int16_t);
            audioSample->sample.sampleAddr = reinterpret_cast<uint8_t *>(pcmData);
            audioSample->sample.codec = CODEC_S16;

            audioSample->loop.start = 0;
            audioSample->loop.end = audioSample->sample.size;
            audioSample->loop.count = 0;
            audioSample->sample.sampleRateMagicValue = 'RIFF';
            audioSample->sample.sampleRate = mp3Info.sampleRate * pitch;
            audioSample->sample.loop = &audioSample->loop;
            break;
        }
        case AudioFormat::FLAC: {
            drflac_uint64 totalPcm;
            uint32_t channels;
            uint32_t sampleRate;
            drmp3_int16* pcmData = drflac_open_memory_and_read_pcm_frames_s16(bytes, length, &channels, &sampleRate, &totalPcm, nullptr);

            audioSample->sample.size = totalPcm * channels * sizeof(int16_t);
            audioSample->sample.sampleAddr = reinterpret_cast<uint8_t *>(pcmData);
            audioSample->sample.codec = CODEC_S16;

            audioSample->loop.start = 0;
            audioSample->loop.end = audioSample->sample.size;
            audioSample->loop.count = 0;
            audioSample->sample.sampleRateMagicValue = 'RIFF';
            audioSample->sample.sampleRate = sampleRate * pitch;
            audioSample->sample.loop = &audioSample->loop;
            break;
        }
    }

    return audioSample;
}
} // namespace SOH
