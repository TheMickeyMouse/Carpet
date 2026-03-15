#pragma once
#include "Constants.h"

namespace Quasi::Math {
    static constexpr MathConstant RAD_2_DEG { 4128596020240314224 }; // π/180, multiply to convert radians to degrees
    static constexpr MathConstant DEG_2_RAD { 1257642267027278    }; // 180/π, multiply to convert degrees to radians

    struct Radians {
        f32 radians;
        explicit Radians(f32 radians) : radians(radians) {}
    public:
        f32 Degrees() const { return RAD_2_DEG * radians; }
        f32 Revolutions() const { return radians / (f32)TAU; }
        void Normalize() { radians = std::fmod(radians, TAU); }

        const f32& operator*() const { return radians; }
        f32& operator*() { return radians; }
        Radians operator+() const { return *this; }
        Radians operator-() const { return Radians(-radians); }
        Radians operator+(Radians theta) const { return Radians(radians + theta.radians); }
        Radians operator-(Radians theta) const { return Radians(radians - theta.radians); }
        Radians operator*(f32 mul) const { return Radians(radians * mul); }
        Radians operator/(f32 div) const { return Radians(radians / div); }
        Radians& operator+=(Radians theta) { radians += theta.radians; return *this; }
        Radians& operator-=(Radians theta) { radians -= theta.radians; return *this; }
        Radians& operator*=(f32 mul) { radians *= mul; return *this; }
        Radians& operator/=(f32 div) { radians /= div; return *this; }
    };

    inline Radians Degrees(float deg) {
        return Radians { deg * DEG_2_RAD };
    }

    inline Radians Revolutions(float rev) {
        return Radians { rev * TAU };
    }

    inline Radians operator ""_rad(long double rad) {
        return Radians((f32)rad);
    }
    inline Radians operator ""_deg(long double deg) {
        return Degrees((f32)deg);
    }
    inline Radians operator ""_rev(long double rev) {
        return Revolutions((f32)rev);
    }

    namespace Trig {
        inline f32 Cos (Radians theta) { return cosf(*theta); }
        inline f32 Sin (Radians theta) { return sinf(*theta); }
        inline f32 Tan (Radians theta) { return tanf(*theta); }
        inline f32 Cosh(Radians theta) { return coshf(*theta); }
        inline f32 Sinh(Radians theta) { return sinhf(*theta); }
        inline f32 Tanh(Radians theta) { return tanhf(*theta); }
        inline Radians Arccos (f32 x) { return (Radians)acosf(x); }
        inline Radians Arcsin (f32 x) { return (Radians)asinf(x); }
        inline Radians Arctan (f32 x) { return (Radians)atanf(x); }
        inline Radians Arccosh(f32 x) { return (Radians)acoshf(x); }
        inline Radians Arcsinh(f32 x) { return (Radians)asinhf(x); }
        inline Radians Arctanh(f32 x) { return (Radians)atanhf(x); }
        inline Radians Atan2(f32 y, f32 x)   { return (Radians)atan2f(y, x); }
        inline Radians AngleOf(f32 x, f32 y) { return (Radians)atan2f(y, x); }
    }
    using namespace Trig;
}

namespace Quasi {
    using Math::operator""_deg;
    using Math::operator""_rad;
    using Math::operator""_rev;
}