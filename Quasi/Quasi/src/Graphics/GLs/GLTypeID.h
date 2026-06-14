#pragma once
#include "Utils/Numeric.h"

namespace Quasi::Graphics {
    struct TID {
        enum E {
            SBYTE  = 0x1400,
            BYTE   = 0x1401,
            SHORT  = 0x1402,
            USHORT = 0x1403,
            INT    = 0x1404,
            UINT   = 0x1405,
            FLOAT  = 0x1406,
            DOUBLE = 0x140A,
            BEGIN  = 0x1400,
        };
        inline static u32 TSIZE[] = {
            sizeof(sbyte),
            sizeof(byte),
            sizeof(short),
            sizeof(ushort),
            sizeof(int),
            sizeof(uint),
            sizeof(float),
            0, 0, 0,
            sizeof(double),
        };
        template <class T> static E Of() = delete;
    };
    template <> inline TID::E TID::Of<float>()  { return FLOAT; }
    template <> inline TID::E TID::Of<double>() { return DOUBLE; }
    template <> inline TID::E TID::Of<int>()    { return INT; }
    template <> inline TID::E TID::Of<uint>()   { return UINT; }
    template <> inline TID::E TID::Of<sbyte>()  { return SBYTE; }
    template <> inline TID::E TID::Of<byte>()   { return BYTE; }
    template <> inline TID::E TID::Of<short>()  { return SHORT; }
    template <> inline TID::E TID::Of<ushort>() { return USHORT; }
}
