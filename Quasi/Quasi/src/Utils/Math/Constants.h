#pragma once
#include "Utils/Numeric.h"

namespace Quasi::Math {
    // a math constant represented by some x / 2^56
    struct MathConstant {
        i64 num56;

        constexpr f64 Value() const { return (double)num56 * (1.0f / (f64)(1ULL << 56)); }
        constexpr operator f64() const { return Value(); }
        constexpr operator f32() const { return (f32)Value(); }

        constexpr f64 operator+() const { return  Value(); }
        constexpr f64 operator-() const { return -Value(); }
        constexpr f64 operator+(f64 x) const { return      Value() + x; }
        constexpr f32 operator+(f32 x) const { return (f32)Value() + x; }
        constexpr f64 operator*(f64 x) const { return      Value() * x; }
        constexpr f32 operator*(f32 x) const { return (f32)Value() * x; }
        constexpr f64 operator-(f64 x) const { return      Value() - x; }
        constexpr f32 operator-(f32 x) const { return (f32)Value() - x; }
        constexpr f64 operator/(f64 x) const { return      Value() / x; }
        constexpr f32 operator/(f32 x) const { return (f32)Value() / x; }
    };
    constexpr f32 operator+(f32 x, MathConstant c) { return x + (f32)c; }
    constexpr f32 operator-(f32 x, MathConstant c) { return x - (f32)c; }
    constexpr f32 operator*(f32 x, MathConstant c) { return x * (f32)c; }
    constexpr f32 operator/(f32 x, MathConstant c) { return x / (f32)c; }
    constexpr f64 operator+(f64 x, MathConstant c) { return x + (f64)c; }
    constexpr f64 operator-(f64 x, MathConstant c) { return x - (f64)c; }
    constexpr f64 operator*(f64 x, MathConstant c) { return x * (f64)c; }
    constexpr f64 operator/(f64 x, MathConstant c) { return x / (f64)c; }
    constexpr f32 operator> (f32 x, MathConstant c) { return x >  (f32)c; }
    constexpr f32 operator>=(f32 x, MathConstant c) { return x >= (f32)c; }
    constexpr f32 operator==(f32 x, MathConstant c) { return x == (f32)c; }
    constexpr f32 operator<=(f32 x, MathConstant c) { return x <= (f32)c; }
    constexpr f32 operator< (f32 x, MathConstant c) { return x <  (f32)c; }
    constexpr f64 operator> (f64 x, MathConstant c) { return x >  (f64)c; }
    constexpr f64 operator>=(f64 x, MathConstant c) { return x >= (f64)c; }
    constexpr f64 operator==(f64 x, MathConstant c) { return x == (f64)c; }
    constexpr f64 operator<=(f64 x, MathConstant c) { return x <= (f64)c; }
    constexpr f64 operator< (f64 x, MathConstant c) { return x <  (f64)c; }

    static constexpr MathConstant PI       { 226375608064910088 }; // π   = 3.14159'26535'89793'23846'26433
    static constexpr MathConstant TAU      { 452751216129820177 }; // τ   = 6.28318'53071'79586'47692'52867
    static constexpr MathConstant HALF_PI  { 113187804032455044 }; // π/2 = 1.57079'63267'94896'61923'13216
    static constexpr MathConstant QUART_PI { 56593902016227522  }; // π/4 = 0.78539'81633'97448'30961'56608
    static constexpr MathConstant INV_PI   { 22936644556890634  }; // 1/π = 0.31830'98861'83790'67153'77675

    static constexpr MathConstant E       { 195872848475778346 }; // e        = 2.71828'18284'59045'23536'02874
    static constexpr MathConstant INV_E   { 26508507426831583  }; // 1/e      = 0.36787'94411'71442'32159'55237
    static constexpr MathConstant LN_2    { 49946518145322873  }; // ln2      = 0.69314'71805'59945'30941'72321
    static constexpr MathConstant LN_10   { 165918741868749488 }; // ln10     = 2.30258'50929'94045'68401'79914
    static constexpr MathConstant LOG2_E  { 103957133576908769 }; // log2(e)  = 1.44269'50408'88963'40735'99246
    static constexpr MathConstant LOG10_E { 31294215469896760  }; // log10(e) = 0.43429'44819'03251'82765'11289

    static constexpr MathConstant ONE_HALF    { 36028797018963968  }; // 1/2  = 0.5
    static constexpr MathConstant ROOT_2      { 101904826760412361 }; // √2   = 1.41421'35623'73095'04880'16887
    static constexpr MathConstant HALF_ROOT_2 { 50952413380206180  }; // √2/2 = 0.70710'67811'86547'52440'08443
    static constexpr MathConstant INV_ROOT_2  = HALF_ROOT_2;            // 1/√2 = 0.70710'67811'86547'52440'08443
    static constexpr MathConstant ROOT_3      { 124807413944863399 }; // √3   = 1.73205'08075'68877'29352'74463
    static constexpr MathConstant HALF_ROOT_3 { 62403706972431699  }; // √3/2 = 0.86602'54037'84438'64676'37231
    static constexpr MathConstant INV_ROOT_3  { 41602471314954466  }; // 1/√3 = 0.57735'02691'89625'76450'91487

    static constexpr MathConstant ROOT_5   { 161125678563890424 }; // √5       =  2.23606'79774'99789'69640'91736
    static constexpr MathConstant PHI      { 116591636300909180 }; // Φ        =  1.61803'39887'49894'84820'45868
    static constexpr MathConstant NINV_PHI { -44534042262981244 }; // φ = -1/Φ = -0.61803'39887'49894'84820'45868

    static constexpr MathConstant SIN30 = HALF_ROOT_3; // sin 30° = √3/2 = 0.86602'54037'84438'64676'37231
    static constexpr MathConstant SIN45 = HALF_ROOT_2; // sin 45° = √2/2 = 0.70710'67811'86547'52440'08443
    static constexpr MathConstant SIN60 = ONE_HALF;    // sin 60° =  1/2 = 0.5
    static constexpr MathConstant COS30 = ONE_HALF;    // cos 30° =  1/2 = 0.5
    static constexpr MathConstant COS45 = HALF_ROOT_2; // cos 45° = √2/2 = 0.70710'67811'86547'52440'08443
    static constexpr MathConstant COS60 = HALF_ROOT_3; // cos 60° = √3/2 = 0.86602'54037'84438'64676'37231

// #define FIXEDP(X) (i64)(X##L * (f64)(1ULL << 56))
//     enum MathConstant {
//         PI          = FIXEDP( 3.14159'26535'89793'23846'26433), // π
//         TAU         = FIXEDP( 6.28318'53071'79586'47692'52867), // τ
//         HALF_PI     = FIXEDP( 1.57079'63267'94896'61923'13216), // π/2
//         QUART_PI    = FIXEDP( 0.78539'81633'97448'30961'56608), // π/4
//         INV_PI      = FIXEDP( 0.31830'98861'83790'67153'77675), // 1/π
//         E           = FIXEDP( 2.71828'18284'59045'23536'02874), // e
//         INV_E       = FIXEDP( 0.36787'94411'71442'32159'55237), // 1/e
//         LN_2        = FIXEDP( 0.69314'71805'59945'30941'72321), // ln2
//         LN_10       = FIXEDP( 2.30258'50929'94045'68401'79914), // ln10
//         LOG2_E      = FIXEDP( 1.44269'50408'88963'40735'99246), // log2(e)
//         LOG10_E     = FIXEDP( 0.43429'44819'03251'82765'11289), // log10(e)
//         ONE_HALF    = FIXEDP( 1.41421'35623'73095'04880'16887), // 1/2
//         ROOT_2      = FIXEDP( 0.70710'67811'86547'52440'08443), // √2
//         HALF_ROOT_2 = FIXEDP( 0.70710'67811'86547'52440'08443), // √2/2
//         ROOT_3      = FIXEDP( 1.73205'08075'68877'29352'74463), // 1/√2
//         HALF_ROOT_3 = FIXEDP( 0.86602'54037'84438'64676'37231), // √3
//         INV_ROOT_3  = FIXEDP( 0.57735'02691'89625'76450'91487), // √3/2
//         ROOT_5      = FIXEDP( 2.23606'79774'99789'69640'91736), // 1/√3
//         PHI         = FIXEDP( 1.61803'39887'49894'84820'45868), // √5
//         NINV_PHI    = FIXEDP(-0.61803'39887'49894'84820'45868), // Φ
//     };
//     static constexpr f64 FIXEDP_INTO = 1.0f / (f64)(1ULL << 56);
//
//     static constexpr f64 operator+(MathConstant c) { return  (c * FIXEDP_INTO); }
//     static constexpr f64 operator-(MathConstant c) { return -(c * FIXEDP_INTO); }
//     static constexpr f64 operator+(MathConstant c, f64 x) { return      Value + x; }
//     static constexpr f32 operator+(MathConstant c, f32 x) { return (f32)Value + x; }
//     static constexpr f64 operator*(MathConstant c, f64 x) { return      Value * x; }
//     static constexpr f32 operator*(MathConstant c, f32 x) { return (f32)Value * x; }
//     static constexpr f64 operator-(MathConstant c, f64 x) { return      Value - x; }
//     static constexpr f32 operator-(MathConstant c, f32 x) { return (f32)Value - x; }
//     static constexpr f64 operator/(MathConstant c, f64 x) { return      Value / x; }
//     static constexpr f32 operator/(MathConstant c, f32 x) { return (f32)Value / x; }
}
