#include "Hash.h"
#include "Span.h"

namespace Quasi::Hashing {
    Hash  AsHash(usize x) { return (Hash)x; }
    usize AsIndex(Hash h) { return (usize)h; }

    Hash HashInt(usize x) {
        // murmur hash 3
        x ^= x >> 33U;
        x *= 0xff51afd7ed558ccd;
        x ^= x >> 33U;
        return AsHash(x);
    }

    Hash HashBytes(Span<const byte> bytes) {
        // from https://github.com/martinus/robin-hood-hashing/blob/master/src/include/robin_hood.h#L692
        static constexpr u64 M_FACTOR = 0xc6a4a7935bd1e995,
                             H_SEED   = 0xe17a1465;
        static constexpr u32 RSHIFT = 47;

        u64 h = H_SEED ^ (bytes.Length() * M_FACTOR);

        const u64 chunkCount = bytes.Length() / 8;
        for (u64 i = 0; i < chunkCount; ++i) {
            u64 k = Memory::ReadU64Native(bytes.Data() + i * 8);

            k *= M_FACTOR;
            k ^= k >> RSHIFT;
            k *= M_FACTOR;

            h ^= k;
            h *= M_FACTOR;
        }

        const byte* lastData = bytes.Data() + chunkCount * 8;
        switch (bytes.Length() & 7) {
            case 7:
                h ^= (usize)lastData[6] << 48; [[fallthrough]];
            case 6:
                h ^= (usize)lastData[5] << 40; [[fallthrough]];
            case 5:
                h ^= (usize)lastData[4] << 32; [[fallthrough]];
            case 4:
                h ^= (usize)lastData[3] << 24; [[fallthrough]];
            case 3:
                h ^= (usize)lastData[2] << 16; [[fallthrough]];
            case 2:
                h ^= (usize)lastData[1] << 8;  [[fallthrough]];
            case 1:
                h ^= (usize)lastData[0];
                h *= M_FACTOR;
            default:
                break;
        }

        h ^= h >> RSHIFT;

        return AsHash(h);
    }

    Hash HashCombine(Hash a, Hash b) {
        return AsHash(a ^ (b + 0x9e3779b9 + (a << 6) + (a >> 2)));
    }
}
