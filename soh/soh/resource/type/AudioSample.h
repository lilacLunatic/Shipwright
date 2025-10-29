#pragma once

#include <cstdint>
#include "Resource.h"
#include <libultraship/libultra/types.h>

namespace SOH {
typedef struct {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
    /* 0x08 */ u32 count;
    /* 0x0C */ char unk_0C[0x4];
    /* 0x10 */ s16 state[16]; // only exists if count != 0. 8-byte aligned
} AdpcmLoop;                  // size = 0x30 (or 0x10)

typedef struct {
    /* 0x00 */ s32 order;
    /* 0x04 */ s32 npredictors;
    /* 0x08 */ s16* book; // size 8 * order * npredictors. 8-byte aligned
} AdpcmBook;              // s

typedef struct {
    union {
        struct {
            /* 0x00 */ u32 codec : 4;
            /* 0x00 */ u32 medium : 2;
            /* 0x00 */ u32 unk_bit26 : 1;
            /* 0x00 */ u32 unk_bit25 : 1; // this has been named isRelocated in zret
        };
        u32 asU32;
    };
    /* 0x01 */ u32 size;
    /* 0x04 */ u8* sampleAddr;
    /* 0x08 */ AdpcmLoop* loop;
    /* 0x0C */ AdpcmBook* book;
} Sample; // size = 0x10

class AudioSample : public Ship::Resource<Sample> {
  public:
    using Resource::Resource;

    AudioSample() : Resource(std::shared_ptr<Ship::ResourceInitData>()) {
    }
    ~AudioSample();

    Sample* GetPointer();
    size_t GetPointerSize();

    Sample sample;
    AdpcmLoop loop;
    AdpcmBook book;
    // Only applies to streamed audio
    float tuning = -1.0f;
};
}; // namespace SOH
