#include "Bitwise.h"

namespace Quasi::Bitwise {
    bool ContainsNullByte(u64 x) {
        // theres an explanation here: https://graphics.stanford.edu/~seander/bithacks.html#ZeroInWord
        static constexpr u64 EXCEPT_FIRST = 0x7F7F7F7F'7F7F7F7F;
        return ~(((x & EXCEPT_FIRST) + EXCEPT_FIRST) | x | EXCEPT_FIRST);
    }

    u32 PlaceOfNullByte(u64 x) {
        static constexpr u64 EXCEPT_FIRST = 0x7F7F7F7F'7F7F7F7F;
        const u64 q = ~(((x & EXCEPT_FIRST) + EXCEPT_FIRST) | x | EXCEPT_FIRST);
        return q ? u64s::CountRightZeros(q) / 8 : 8;
    }

    bool ContainsByte(u64 x, byte b) {
        return ContainsNullByte(x ^ (b * 0x0101010101010101));
    }

    bool BytesAllWithinRange(u64 x, byte min, byte max) {
        const u64 a = x + 0x8080'8080'8080'8080 - max * 0x0101'0101'0101'0101;
        const u64 b = x                         - min * 0x0101'0101'0101'0101;
        return ((a | b) & 0x8080'8080'8080'8080) == 0;
    }

    u32 Add4Bytes(u32 a, u32 b) {
        static constexpr u32 EVEN_BYTES = 0xFF00FF00, ODD_BYTES = ~EVEN_BYTES;
        return (((a & EVEN_BYTES) + (b & EVEN_BYTES)) & EVEN_BYTES) |
               (((a &  ODD_BYTES) + (b &  ODD_BYTES)) &  ODD_BYTES);
    }

    u64 Add8Bytes(u64 a, u64 b) {
        static constexpr u64 EVEN_BYTES = 0xFF00FF00FF00FF00, ODD_BYTES = ~EVEN_BYTES;
        return (((a & EVEN_BYTES) + (b & EVEN_BYTES)) & EVEN_BYTES) |
               (((a &  ODD_BYTES) + (b &  ODD_BYTES)) &  ODD_BYTES);
    }

    bool BitXorReduce(byte b8) {
        return (((b8 * 0x0101010101010101ULL) & 0x8040201008040201ULL) % 0x1FF) & 1;
    }

    bool BitXorReduce(u32 b32) {
        b32 ^= b32 >> 1;
        b32 ^= b32 >> 2;
        b32 = (b32 & 0x11111111U) * 0x11111111U;
        return (b32 >> 28) & 1;
    }

    bool BitXorReduce(u64 b64) {
        b64 ^= b64 >> 1;
        b64 ^= b64 >> 2;
        b64 = (b64 & 0x1111111111111111UL) * 0x1111111111111111UL;
        return (b64 >> 60) & 1;
    }

    byte BitReverse(byte b8) {
        return ((b8 * 0x80200802ULL) & 0x0884422110ULL) * 0x0101010101ULL >> 32;
    }

    u32 RoundPow2(u32 x) {
        x--;
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        return x + 1;
    }

    u32 NextBitPerm(u32 perm) {
        // see https://graphics.stanford.edu/~seander/bithacks.html#NextBitPermutation
        const u32 t = perm | (perm - 1); // t gets v's least significant 0 bits set to 1
        // Next set to 1 the most significant bit to change,
        // set to 0 the least significant ones, and add the necessary 1 bits.
        return (t + 1) | (((~t & -~t) - 1) >> (u32s::CountRightZeros(perm) + 1));
    }

    u64 NextBitPerm(u64 perm) {
        const u64 t = perm | (perm - 1);
        return (t + 1) | (((~t & -~t) - 1) >> (u64s::CountRightZeros(perm) + 1));
    }
}
