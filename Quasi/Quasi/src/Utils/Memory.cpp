#include <cstring>

#include "Memory.h"

namespace Quasi {
    void* Memory::AllocateRaw(usize size) {
        return ::operator new (size);
    }

    void Memory::FreeRaw(void* mem) {
        return ::operator delete (mem);
    }

    u16 Memory::ReadU16Big(const void* bytes) {
        const auto b = (const byte*)bytes;
        return (u16)b[0] << 8 | (u16)b[1];
    }
    u32 Memory::ReadU32Big(const void* bytes) {
        const auto b = (const byte*)bytes;
        return (u32)b[0] << 24 | (u32)b[1] << 16 | (u32)b[2] << 8 | (u32)b[3];
    }
    u64 Memory::ReadU64Big(const void* bytes) {
        const auto b = (const byte*)bytes;
        return (u64)b[0] << 56 | (u64)b[1] << 48 | (u64)b[2] << 40 | (u64)b[3] << 32 |
               (u64)b[4] << 24 | (u64)b[5] << 16 | (u64)b[6] <<  8 | (u64)b[7];
    }
    i16 Memory::ReadI16Big(const void* bytes) { return (i16)ReadU16Big(bytes); }
    i32 Memory::ReadI32Big(const void* bytes) { return (i32)ReadU32Big(bytes); }
    i64 Memory::ReadI64Big(const void* bytes) { return (i64)ReadU64Big(bytes); }

    u16 Memory::ReadU16(const void* bytes) {
        const auto b = (const byte*)bytes;
        return (u16)b[1] << 8 | (u16)b[0];
    }
    u32 Memory::ReadU32(const void* bytes) {
        const auto b = (const byte*)bytes;
        return (u32)b[3] << 24 | (u32)b[2] << 16 | (u32)b[1] << 8 | (u32)b[0];
    }
    u64 Memory::ReadU64(const void* bytes) {
        const auto b = (const byte*)bytes;
        return (u64)b[7] << 56 | (u64)b[6] << 48 | (u64)b[5] << 40 | (u64)b[4] << 32 |
               (u64)b[3] << 24 | (u64)b[2] << 16 | (u64)b[1] <<  8 | (u64)b[0];
    }
    i16 Memory::ReadI16(const void* bytes) { return (i16)ReadU16(bytes); }
    i32 Memory::ReadI32(const void* bytes) { return (i32)ReadU32(bytes); }
    i64 Memory::ReadI64(const void* bytes) { return (i64)ReadU64(bytes); }

    u16 Memory::ReadU16Native(const void* bytes) { u16 x; MemCopyNoOverlap(&x, bytes, sizeof(u16)); return x; }
    u32 Memory::ReadU32Native(const void* bytes) { u32 x; MemCopyNoOverlap(&x, bytes, sizeof(u32)); return x; }
    u64 Memory::ReadU64Native(const void* bytes) { u64 x; MemCopyNoOverlap(&x, bytes, sizeof(u64)); return x; }
    i16 Memory::ReadI16Native(const void* bytes) { i16 x; MemCopyNoOverlap(&x, bytes, sizeof(i16)); return x; }
    i32 Memory::ReadI32Native(const void* bytes) { i32 x; MemCopyNoOverlap(&x, bytes, sizeof(i32)); return x; }
    i64 Memory::ReadI64Native(const void* bytes) { i64 x; MemCopyNoOverlap(&x, bytes, sizeof(i64)); return x; }

    u16 Memory::ReadZeroExtU16(const void* bytes, usize len) {
        if (len == 0) return 0;
        return len == 1 ? *(const byte*)bytes : ReadU16(bytes);
    }
    u32 Memory::ReadZeroExtU32(const void* bytes, usize len) {
        if (len == 0) return 0;
        len = std::min<usize>(len, 4) * 8;
        return ReadU32(bytes) & ~(~0u << len);
    }
    u64 Memory::ReadZeroExtU64(const void* bytes, usize len) {
        if (len == 0) return 0;
        len = std::min<usize>(len, 8) * 8;
        return ReadU64(bytes) & ~(~0ull << len);
    }

    u16 Memory::ReadZeroExtU16Big(const void* bytes, usize len) {
        if (len == 0) return 0;
        return len == 1 ? *(const byte*)bytes : ReadU16Big(bytes);
    }

    u32 Memory::ReadZeroExtU32Big(const void* bytes, usize len) {
        if (len == 0) return 0;
        len = std::min<usize>(len, 4) * 8;
        return ReadU32Big(bytes) >> (-len & 31);
    }

    u64 Memory::ReadZeroExtU64Big(const void* bytes, usize len) {
        if (len == 0) return 0;
        len = std::min<usize>(len, 8) * 8;
        return ReadU64Big(bytes) >> (-len & 63);
    }

    void Memory::WriteU16Big(u16 x, void* out) {
        const auto b = (byte*)out;
        b[0] = x >> 8; b[1] = x;
    }
    void Memory::WriteU32Big(u32 x, void* out) {
        const auto b = (byte*)out;
        b[0] = x >> 24; b[1] = x >> 16; b[2] = x >> 8; b[3] = x;
    }
    void Memory::WriteU64Big(u64 x, void* out) {
        const auto b = (byte*)out;
        b[0] = x >> 56; b[1] = x >> 48; b[2] = x >> 40; b[3] = x >> 32;
        b[4] = x >> 24; b[5] = x >> 16; b[6] = x >> 8;  b[7] = x;
    }

    void Memory::WriteI16Big(i16 x, void* out) { WriteU16Big((u16)x, out); }
    void Memory::WriteI32Big(i32 x, void* out) { WriteU32Big((u32)x, out); }
    void Memory::WriteI64Big(i64 x, void* out) { WriteU64Big((u64)x, out); }

    void Memory::WriteU16(u16 x, void* out) {
        const auto b = (byte*)out;
        b[1] = x >> 8;  b[0] = x;
    }
    void Memory::WriteU32(u32 x, void* out) {
        const auto b = (byte*)out;
        b[3] = x >> 24; b[2] = x >> 16; b[1] = x >> 8;  b[0] = x;
    }
    void Memory::WriteU64(u64 x, void* out) {
        const auto b = (byte*)out;
        b[7] = x >> 56; b[6] = x >> 48; b[5] = x >> 40; b[4] = x >> 32;
        b[3] = x >> 24; b[2] = x >> 16; b[1] = x >> 8;  b[0] = x;
    }

    void Memory::WriteI16(i16 x, void* out) { WriteU16((u16)x, out); }
    void Memory::WriteI32(i32 x, void* out) { WriteU32((u32)x, out); }
    void Memory::WriteI64(i64 x, void* out) { WriteU64((u64)x, out); }

    void Memory::WriteU16Native(u16 x, void* out) { MemCopyNoOverlap(out, &x, sizeof(u16)); }
    void Memory::WriteU32Native(u32 x, void* out) { MemCopyNoOverlap(out, &x, sizeof(u32)); }
    void Memory::WriteU64Native(u64 x, void* out) { MemCopyNoOverlap(out, &x, sizeof(u64)); }
    void Memory::WriteI16Native(i16 x, void* out) { MemCopyNoOverlap(out, &x, sizeof(i16)); }
    void Memory::WriteI32Native(i32 x, void* out) { MemCopyNoOverlap(out, &x, sizeof(i32)); }
    void Memory::WriteI64Native(i64 x, void* out) { MemCopyNoOverlap(out, &x, sizeof(i64)); }

    u16 Memory::ByteSwap16(u16 x) { return (x << 8) | (x >> 8); }
    u32 Memory::ByteSwap32(u32 x) {
        x     = x << 16 | x >> 16;
        return (x & 0xFF00FF00) >> 8 | (x & 0x00FF00FF) << 8;
    }
    u64 Memory::ByteSwap64(u64 x) {
        x    =  x << 32 | x >> 32;
        x    = (x & 0xFFFF0000FFFF0000) >> 16 | (x & 0x0000FFFF0000FFFF) << 16;
        return (x & 0xFF00FF00FF00FF00) >> 8  | (x & 0x00FF00FF00FF00FF) << 8;
    }

    void Memory::MemCopy(void* out, const void* in, usize bytes) {
        for (usize i = 0; i < bytes; ++i)
            ((byte*)out)[i] = ((byte*)in)[i];
    }

    void Memory::MemCopyNoOverlap(void* out, const void* in, usize bytes) {
        std::memcpy(out, in, bytes);
    }

    void Memory::MemCopyRev(void* out, const void* in, usize bytes) {
        for (usize i = bytes; i --> 0; )
            ((byte*)out)[i] = ((byte*)in)[i];
    }

    void Memory::MemSet(void* dest, byte value, usize bytes) {
        for (usize i = 0; i < bytes; ++i)
            ((byte*)dest)[i] = value;
    }

    void Memory::MemSwap(void* a, void* b, usize bytes) {
        byte* p1 = (byte*)a, *p2 = (byte*)b;
        while (bytes--) {
            const byte tmp = *p1;
            *p1++ = *p2;
            *p2++ = tmp;
        }
    }

    void Memory::MemReverse(void* arr, usize bytes) {
        byte* lo = (byte*)arr, *hi = lo + bytes - 1;
        while (lo < hi) {
            const byte tmp = *lo;
            *lo++ = *hi;
            *hi-- = tmp;
        }
    }
}
