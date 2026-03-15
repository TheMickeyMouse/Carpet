#pragma once
#include <cstdint>
#include <cfloat>
#include <cmath>
#include <bit>

#undef NAN
#undef INFINITY

namespace Quasi {
    using i8   = std::int8_t;
    using i16  = std::int16_t;
    using i32  = std::int32_t;
    using i64  = std::int64_t;
    using u8   = std::uint8_t;
    using u16  = std::uint16_t;
    using u32  = std::uint32_t;
    using u64  = std::uint64_t;
    using f32  = float;
    using f64  = double;
    using ushort = u16;
    using ulong  = u64;
    using usize  = std::size_t;
    using isize  = std::intptr_t;

    using uchar = unsigned char;
    using byte  = unsigned char;
    using sbyte = signed char;
    using uint  = unsigned int;

    template <class T> concept Integer   = std::is_integral_v<T>;
    template <class T> concept Signed    = std::is_signed_v<T>;
    template <class T> concept Unsigned  = std::is_unsigned_v<T>;
    template <class T> concept Floating  = std::is_floating_point_v<T>;
    template <class T> concept Numeric   = std::is_arithmetic_v<T>;

    template <class T> using IntoSigned   = std::make_signed_t<T>;
    template <class T> using IntoUnsigned = std::make_unsigned_t<T>;

    template <class T> struct NumInfo {};

    namespace Math {
        static constexpr u32 LOG2_LOOKUP[37] = {
            0,      0,      65536,  103872, 131072, 152169,
            169408, 183982, 196608, 207744, 217705, 226717,
            234944, 242512, 249518, 256041, 262144, 267875,
            273280, 278392, 283241, 287854, 292253, 296456,
            300480, 304339, 308048, 311616, 315054, 318372,
            321577, 324678, 327680, 330589, 333411, 336152, 338816
        };
        static constexpr u32 INV_LOG2_LOOKUP[37] = {
            ~0u,   ~0u,   65536, 41348, 32768, 28224,
            25352, 23344, 21845, 20674, 19728, 18944,
            18280, 17710, 17212, 16774, 16384, 16033,
            15716, 15427, 15163, 14920, 14696, 14487,
            14293, 14112, 13942, 13782, 13632, 13490,
            13355, 13228, 13107, 12991, 12881, 12776, 12676
        };
        static constexpr u64 POWERS_OF_10[20] = {
            1ULL,
            10ULL,
            100ULL,
            1'000ULL,
            10'000ULL,
            100'000ULL,
            1'000'000ULL,
            10'000'000ULL,
            100'000'000ULL,
            1'000'000'000ULL,
            10'000'000'000ULL,
            100'000'000'000ULL,
            1'000'000'000'000ULL,
            10'000'000'000'000ULL,
            100'000'000'000'000ULL,
            1'000'000'000'000'000ULL,
            10'000'000'000'000'000ULL,
            100'000'000'000'000'000ULL,
            1'000'000'000'000'000'000ULL,
            10'000'000'000'000'000'000ULL,
        };

        // a fractional approximation of log_2(10). = 217706 / 2^16
        static constexpr usize LOG10_2_MUL     = LOG2_LOOKUP[10];
        // a fractional approximation of 1 / log_2(10). = 19728 / 2^16
        static constexpr usize INV_LOG10_2_MUL = INV_LOG2_LOOKUP[10];
        static constexpr f64 LOG10_2 = 3.321928094887362f;
    }

    template <Integer N>
    struct NumInfo<N> {
        using UnsignedInt = IntoUnsigned<N>;

        static constexpr bool  IS_SIGNED = ((N)-1) < 0;
        static constexpr N     MAX       = (N)~(IS_SIGNED ? (N)1 << (sizeof(N) * 8 - 1) : 0);
        static constexpr N     MIN       = (N)~MAX;
        static constexpr usize BITS      = sizeof(N) * 8;
        static constexpr usize HEX_DIGITS = sizeof(N) * 2;
        static constexpr usize DIGITS    = 1 + ((BITS - IS_SIGNED) * Math::INV_LOG10_2_MUL >> 16);

        static bool AddOverflow(N a, N b, N& out) { return __builtin_add_overflow(a, b, &out); }
        static bool SubOverflow(N a, N b, N& out) { return __builtin_sub_overflow(a, b, &out); }
        static bool MulOverflow(N a, N b, N& out) { return __builtin_mul_overflow(a, b, &out); }

        static u32  CountOnes (N x) { return std::popcount((UnsignedInt)x); }
        static u32  CountZeros(N x) { return std::popcount((UnsignedInt)~(UnsignedInt)x); }
        static u32  CountLeftZeros (N x) { return std::countl_zero((UnsignedInt)x); }
        static u32  CountLeftOnes  (N x) { return std::countl_one ((UnsignedInt)x); }
        static u32  CountRightZeros(N x) { return std::countr_zero((UnsignedInt)x); }
        static u32  CountRightOnes (N x) { return std::countr_one ((UnsignedInt)x); }
        static bool IsPow2    (N x) { return x && !(x & (x - 1)); }
        static u32  BitWidth  (N x) { return std::bit_width((UnsignedInt)x); }
        static u32  Log2      (N x) { return BitWidth(x) - 1; }
        static u32  Log10     (N x) {
            u32 approx10 = BitWidth(x) * Math::INV_LOG10_2_MUL >> 16;
            return approx10 - (x < Math::POWERS_OF_10[approx10]);
        }

        static N Modulo(N a, N b) { return a % b; } // used to overload floating modulo
        static N CopySign(N x, N sign) requires Unsigned<N> { return ((x < 0) == (sign < 0)) ? x : -x; } // used to generalize floats
        static N AsSign(bool sign) { return sign - !sign; }
        static N Signed(bool sign, N val) { return sign ? val : -val; }
    };

    using i8s    = NumInfo<i8>;
    using u8s    = NumInfo<u8>;
    using i16s   = NumInfo<i16>;
    using u16s   = NumInfo<u16>;
    using i32s   = NumInfo<i32>;
    using u32s   = NumInfo<u32>;
    using i64s   = NumInfo<i64>;
    using u64s   = NumInfo<u64>;
    using isizes = NumInfo<isize>;
    using usizes = NumInfo<usize>;
    static constexpr i8    operator ""_i8   (unsigned long long x) { return (i8)x; }
    static constexpr u8    operator ""_u8   (unsigned long long x) { return (u8)x; }
    static constexpr i16   operator ""_i16  (unsigned long long x) { return (i16)x; }
    static constexpr u16   operator ""_u16  (unsigned long long x) { return (u16)x; }
    static constexpr i32   operator ""_i32  (unsigned long long x) { return (i32)x; }
    static constexpr u32   operator ""_u32  (unsigned long long x) { return (u32)x; }
    static constexpr i64   operator ""_i64  (unsigned long long x) { return (i64)x; }
    static constexpr u64   operator ""_u64  (unsigned long long x) { return (u64)x; }
    static constexpr isize operator ""_isize(unsigned long long x) { return (isize)x; }
    static constexpr usize operator ""_usize(unsigned long long x) { return (usize)x; }

    enum class FpClassification {
        NAN     = FP_NAN,
        INF     = FP_INFINITE,
        ZERO    = FP_ZERO,
        SUBNORM = FP_SUBNORMAL,
        NORM    = FP_NORMAL,
    };

#define QUASI_DEFINE_FLOATING(FLOAT, CCODENAME, SAME_SIZED, SAME_SIZED_SIGNED) \
    template <> struct NumInfo<FLOAT> { \
        static constexpr FLOAT INFINITY     =  (FLOAT)__builtin_inff(); \
        static constexpr FLOAT NEG_INFINITY = -(FLOAT)__builtin_inff(); \
        static constexpr FLOAT MAX          =  CCODENAME##_MAX; \
        static constexpr FLOAT MIN          = -CCODENAME##_MAX; \
        static constexpr FLOAT EPSILON      =  CCODENAME##_MIN; \
        static constexpr FLOAT TRUE_EPSILON =  CCODENAME##_TRUE_MIN; \
        static constexpr FLOAT DELTA        =  CCODENAME##_EPSILON; \
        static constexpr FLOAT NAN          =  (FLOAT)__builtin_nanf(""); \
        static constexpr int   MAX_EXP      =  CCODENAME##_MAX_EXP; \
        static constexpr int   MIN_EXP      =  CCODENAME##_MIN_EXP; \
        static constexpr int   MAX_EXP10    =  CCODENAME##_MAX_10_EXP; \
        static constexpr int   MIN_EXP10    =  CCODENAME##_MIN_10_EXP; \
        static constexpr usize DIGITS       =  CCODENAME##_MANT_DIG; \
        \
        static constexpr usize BITS          = sizeof(FLOAT) * 8; \
        static constexpr usize EXPONENT_BITS = 5 + sizeof(FLOAT) / 4 * 3; \
        static constexpr usize MANTISSA_BITS = BITS - EXPONENT_BITS - 1; \
        \
        using EquivalentInt = SAME_SIZED; \
        using EquivalentIntSigned = SAME_SIZED_SIGNED; \
        static constexpr SAME_SIZED SIGN_MASK     =  (SAME_SIZED)1 << (sizeof(FLOAT) * 8 - 1); \
        static constexpr SAME_SIZED MANTISSA_MASK = ((SAME_SIZED)1 << MANTISSA_BITS) - 1; \
        static constexpr SAME_SIZED EXPONENT_MASK = ((SAME_SIZED)1 << EXPONENT_BITS) - MANTISSA_MASK - 1; \
        \
        static FLOAT FromBits(SAME_SIZED x) { return __builtin_bit_cast(FLOAT, x); } \
        static SAME_SIZED BitsOf(FLOAT f)   { return __builtin_bit_cast(SAME_SIZED, f); } \
        static bool IsSignedNegative(FLOAT f) { return (BitsOf(f) & SIGN_MASK) != 0; } \
        static bool IsSignedPositive(FLOAT f) { return (BitsOf(f) & SIGN_MASK) == 0; } \
        static FLOAT Sign(FLOAT f) { return f == 0 ? f : f > 0 ? 1 : f < 0 ? -1 : NAN; } \
        static FLOAT CopySign(FLOAT f, FLOAT sign) { return std::copysign(f, sign); } \
        static FLOAT AsSign(bool sign) { return sign ? (FLOAT)1 : (FLOAT)-1; } \
        static FLOAT Signed(bool sign, FLOAT val) { return sign ? val : -val; } \
        \
        static void  Decomp(FLOAT f, int& exp, FLOAT& mant) { mant = std::frexp(f, &exp); } \
        static FLOAT Comp(int exp, FLOAT mant) { return std::ldexp(mant, exp); } \
        static FLOAT Log2(FLOAT x)  { return std::log2(x); } \
        static int   Log2i(FLOAT x) { return std::ilogb(x); } \
        static FLOAT Log10(FLOAT x) { return std::log10(x); } \
        static FLOAT Exp2(FLOAT x)  { return std::exp2(x); } \
        static FLOAT Exp2i(int x)   { return Comp(x, (FLOAT)1); } \
        static FLOAT Exp10(FLOAT x) { return std::pow((FLOAT)10.0, x); } \
        static void  SeparateDecimal(FLOAT x, FLOAT& integer, FLOAT& decimal) { decimal = std::modf(x, &integer); } \
        \
        /* uses bit manipulating techniques to convert floats to ints 100% accurately for values in range [0, 2^23), or [0, 2^52) for doubles */ \
        static SAME_SIZED FastToIntUnsigned(FLOAT f)  { return BitsOf(f +  FLOAT((SAME_SIZED)1 << MANTISSA_BITS)) & MANTISSA_MASK; } \
        static SAME_SIZED FloorToIntUnsigned(FLOAT f) { return BitsOf(f + (FLOAT((SAME_SIZED)1 << MANTISSA_BITS) - FLOAT(0.5))) & MANTISSA_MASK; } \
        static SAME_SIZED CeilToIntUnsigned(FLOAT f)  { return BitsOf(f + (FLOAT((SAME_SIZED)1 << MANTISSA_BITS) + FLOAT(0.5))) & MANTISSA_MASK; } \
        /* uses bit manipulating techniques to convert ints to floats 100% accurately for values in range [0, 2^23), or [0, 2^52) for doubles */ \
        static FLOAT FastToFloatUnsigned(SAME_SIZED x) { return FromBits(x + __builtin_bit_cast(SAME_SIZED, (FLOAT)((SAME_SIZED)1 << MANTISSA_BITS))) - (FLOAT)((SAME_SIZED)1 << MANTISSA_BITS); } \
        \
        static FLOAT FastFloor(FLOAT x) { return FastToFloatUnsigned(FastToIntUnsigned(x)); } \
        \
        static FpClassification Classify(FLOAT f) { return (FpClassification)std::fpclassify(f); } \
        static bool IsNaN(FLOAT f)     { return std::isnan(f); } \
        static bool IsInf(FLOAT f)     { return f == INFINITY || f == NEG_INFINITY; } \
        static bool IsFinite(FLOAT f)  { return std::abs(f) < INFINITY; } \
        static bool IsSubnorm(FLOAT f) { return Classify(f) == FpClassification::SUBNORM; } \
        static bool IsNorm(FLOAT f)    { return Classify(f) == FpClassification::NORM; } \
        \
        static FLOAT ImmediateIncr(FLOAT f) { \
            const SAME_SIZED bits = BitsOf(f); \
            if (IsNaN(f) || bits == BitsOf(INFINITY)) return f; \
            return FromBits(bits + 1); \
        } \
        static FLOAT ImmediateDecr(FLOAT f) { \
            const SAME_SIZED bits = BitsOf(f); \
            if (IsNaN(f) || bits == BitsOf(NEG_INFINITY)) return f; \
            return FromBits(bits - 1); \
        } \
        \
        static FLOAT Max(FLOAT a, FLOAT b) { return std::max(a, b); } \
        static FLOAT Min(FLOAT a, FLOAT b) { return std::min(a, b); } \
        static FLOAT Clamp(FLOAT x, FLOAT min, FLOAT max) { return x < min ? min : x > max ? max : x; } \
        /* returns the max, except if either is nan the result is nan, and positive zero is greater than negative zero */ \
        static FLOAT StrictMax(FLOAT a, FLOAT b) { \
            return a >  b ? a : \
                   b >  a ? b : \
                   a == b ? IsSignedPositive(a) && IsSignedNegative(b) ? a : b : \
                   a + b; \
        } \
        /* returns the min, except if either is nan the result is nan, and positive zero is less than negative zero */ \
        static FLOAT StrictMin(FLOAT a, FLOAT b) { \
            return a >  b ? b : \
                   b >  a ? a : \
                   a == b ? IsSignedNegative(a) && IsSignedPositive(b) ? a : b : \
                   a + b; \
        } \
        \
        /* handles all cases, ordered by:
            -nan < -inf < -norm < -subnorm < -0 < 0 < subnorm < norm < inf < nan
        */ \
        static int CompleteCmp(FLOAT a, FLOAT b) { \
            SAME_SIZED_SIGNED ax = (SAME_SIZED_SIGNED)BitsOf(a), bx = (SAME_SIZED_SIGNED)BitsOf(b); \
            ax ^= (SAME_SIZED_SIGNED)((SAME_SIZED)(ax >> (8 * sizeof(FLOAT) - 1)) >> 1); \
            bx ^= (SAME_SIZED_SIGNED)((SAME_SIZED)(bx >> (8 * sizeof(FLOAT) - 1)) >> 1); \
            return ax - bx; \
        } \
        \
        static FLOAT Modulo(FLOAT a, FLOAT b) { return std::fmod(a, b); } \
    }; \
    using FLOAT##s = NumInfo<FLOAT>;

    QUASI_DEFINE_FLOATING(f32, FLT, u32, i32);
    QUASI_DEFINE_FLOATING(f64, DBL, u64, i64);

#undef QUASI_DEFINE_FLOATING

    namespace Math {
        template <class T>
        T Clamp(T x, T min = (T)0, T max = (T)0) { return x < min ? min : (x > max ? max : x); }
    }
}
