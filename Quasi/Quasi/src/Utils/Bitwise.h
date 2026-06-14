#pragma once
#include "Numeric.h"

namespace Quasi::Bitwise {
    bool ContainsNullByte(u64 x);
    u32 PlaceOfNullByte(u64 x); // this uses big endian: 01234567 where 0 is the highest position, && assumes there is a null byte
    bool ContainsByte(u64 x, byte b);
    bool ContainsLtByte(u64 x, byte b);

    bool BytesAllWithinRange(u64 x, byte min, byte max);

    // different from plain addition, bytes do not overflow to other bytes
    u32 Add4Bytes(u32 a, u32 b);
    u64 Add8Bytes(u64 a, u64 b);

    bool BitXorReduce(byte b8);
    bool BitXorReduce(u32 b32);
    bool BitXorReduce(u64 b64);

    byte BitReverse(byte b8);

    u32 RoundPow2(u32 x);

    u32 NextBitPerm(u32 perm);
    u64 NextBitPerm(u64 perm);
}
