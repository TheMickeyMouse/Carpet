#pragma once
#include <algorithm>

#include "Vector.h"
#include "Utils/Numeric.h"

namespace Quasi::Math {
    // a packed vector of floats, normalized for [0.0-1.0] to [0-255]!
    inline u8 Pack(float x) {
        return (u8)(x * 255.0f);
    }
    inline u8 Pack(float x, CheckedMarker) {
        return (u8)(std::clamp(x, 0.0f, 1.0f) * 255.0f);
    }
    inline u16 PackShort(float x) {
        return (u16)(x * 65535.0f);
    }
    inline u16 PackShort(float x, CheckedMarker) {
        return (u16)(std::clamp(x, 0.0f, 1.0f) * 65535.0f);
    }
    inline float Unpack(u8 x) {
        return (float)x / 255.0f;
    }
    inline float UnpackShort(u16 x) {
        return (float)x / 65536.0f;
    }

    struct IPackedVector {};

    // packed version of fv2 [0-1], which stores values in bytes. 2 bytes instead of 8!
    struct bfv2 : IPackedVector {
        using Elm = u8;
        enum { Dim = 2 };
        u8 x, y;
        bfv2(u8 _x, u8 _y) : x(_x), y(_y) {}
        bfv2(const fv2& v)                : x(Pack(v.x)),          y(Pack(v.y)) {}
        bfv2(const fv2& v, CheckedMarker) : x(Pack(v.x, Checked)), y(Pack(v.y, Checked)) {}
        // lsb is x, then y...
        static bfv2 FromInt   (u32 xy) { return { (u8)(xy & 0xFF), (u8)((xy & 0xFF) >> 8) }; }
        // lsb is y, then x...
        static bfv2 FromIntBig(u32 yx) { return FromInt(Memory::ByteSwap32(yx) >> 16); }
        u32 ToInt() const { return x | (y << 8); }

        operator fv2() const { return { Unpack(x), Unpack(y) }; }
    };

    // shrunken version of fv2 [0-1], which stores values in shorts/u16s. in 4 bytes instead of 8!
    struct sfv2 : IPackedVector {
        using Elm = u16;
        enum { Dim = 2 };
        u16 x, y;
        sfv2(u16 _x, u16 _y) : x(_x), y(_y) {}
        sfv2(const fv2& v)                : x(PackShort(v.x)),          y(PackShort(v.y)) {}
        sfv2(const fv2& v, CheckedMarker) : x(PackShort(v.x, Checked)), y(PackShort(v.y, Checked)) {}
        // lsb is x, then y...
        static sfv2 FromInt   (u32 xy) { return { (u8)(xy & 0xFFFF), (u8)((xy & 0xFFFF) >> 16) }; }
        // lsb is y, then x...
        static sfv2 FromIntBig(u32 yx) { return FromInt(Memory::ByteSwap32(yx)); }
        u32 ToInt() const { return x | (y << 16); }

        operator fv2() const { return { UnpackShort(x), UnpackShort(y) }; }
    };

    // packed version of fv3 [0-1], which stores values in bytes. in 3 bytes instead of 24!
    struct bfv3 : IPackedVector {
        using Elm = u8;
        enum { Dim = 3 };
        u8 x, y, z;
        bfv3(u8 x, u8 y, u8 z) : x(x), y(y), z(z) {}
        bfv3(const fv3& v)                : x(Pack(v.x)),          y(Pack(v.y)),          z(Pack(v.z)) {}
        bfv3(const fv3& v, CheckedMarker) : x(Pack(v.x, Checked)), y(Pack(v.y, Checked)), z(Pack(v.z, Checked)) {}
        // lsb is x, then y...
        static bfv3 FromInt   (u32 xyz) { return { (u8)(xyz & 0xFF), (u8)((xyz & 0xFF) >> 8), (u8)((xyz & 0xFF) >> 16) }; }
        // lsb is z, then y...
        static bfv3 FromIntBig(u32 zyx) { return FromInt(Memory::ByteSwap32(zyx) >> 8); }
        u32 ToInt() const { return x | (y << 8) | (z << 16); }

        operator fv3() const { return { Unpack(x), Unpack(y), Unpack(z) }; }
    };

    // packed version of fv4 [0-1], which stores values in bytes. 4 bytes instead of 32!
    struct bfv4 : IPackedVector {
        using Elm = u8;
        enum { Dim = 4 };
        u8 x, y, z, w;
        bfv4(u8 x, u8 y, u8 z, u8 w) : x(x), y(y), z(z), w(w) {}
        bfv4(const fv4& v)                : x(Pack(v.x)),          y(Pack(v.y)),          z(Pack(v.z)),          w(Pack(v.w)) {}
        bfv4(const fv4& v, CheckedMarker) : x(Pack(v.x, Checked)), y(Pack(v.y, Checked)), z(Pack(v.z, Checked)), w(Pack(v.w, Checked)) {}
        // lsb is x, then y...
        static bfv4 FromInt   (u32 xyzw) { return { (u8)(xyzw & 0xFF), (u8)((xyzw & 0xFF) >> 8), (u8)((xyzw & 0xFF) >> 16), (u8)((xyzw & 0xFF) >> 24) }; }
        // lsb is w, then z...
        static bfv4 FromIntBig(u32 wzyx) { return FromInt(Memory::ByteSwap32(wzyx)); }
        u32 ToInt() const { return x | (y << 8) | (z << 16) | (w << 24); }

        operator fv4() const { return { Unpack(x), Unpack(y), Unpack(z), Unpack(w) }; }
    };
}
