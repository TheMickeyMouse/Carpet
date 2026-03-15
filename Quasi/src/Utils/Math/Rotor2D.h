#pragma once
#include "Complex.h"

namespace Quasi::Math {
    struct Rotor2D : private fComplex {
        Rotor2D() : fComplex(1, 0) {}
        Rotor2D(Radians theta) : fComplex(Math::Cos(theta), Math::Sin(theta)) {}
    private:
        Rotor2D(const fComplex& c) : fComplex(c) {}
    public:
        static Rotor2D FromComplex(const fComplex& c) { return { c }; }
        static Rotor2D FromUnitVector(const fv2& c) { return fComplex { c.x, c.y }; }
        fComplex&       AsComplex()       { return static_cast<fComplex&>(*this); }
        const fComplex& AsComplex() const { return static_cast<const fComplex&>(*this); }

        fv2 AsUnitVector() const { return { re, im }; }
        fv2 IHat() const { return {  re, im }; }
        fv2 JHat() const { return { -im, re }; }
        f32 Cos() const { return re; }
        f32 Sin() const { return im; }

        Radians Angle() const;
        Radians AngleBetween(const Rotor2D& other) const;

        Rotor2D RotateCCW90() const;
        Rotor2D RotateCW90()  const;
        Rotor2D Rotate180()   const;
        Rotor2D RotateBy(Radians theta) const;
        Rotor2D RotateBy   (const Rotor2D& r) const;
        Rotor2D RotateByInv(const Rotor2D& r) const;

        Rotor2D Halved() const;
        Rotor2D HalvedCCW() const;
        Rotor2D Mul(f32 p) const;
        Rotor2D Doubled()  const { return Squared(); }
        Rotor2D Tripled()  const { return Cubed(); }
        Rotor2D Inverse()  const { return Conj(); }

        Matrix2x2 AsMatrixLinear() const { return AsComplex().AsMatrixLinear(); }
        Matrix2D  AsMatrix()       const { return AsComplex().AsMatrix(); }
        fv2 Rotate   (const fv2& v) const;
        fv2 InvRotate(const fv2& v) const;

        Rotor2D Lerp(const Rotor2D& z, f32 t) const;

        Rotor2D operator+() const { return *this; }
        Rotor2D operator-() const { return Inverse(); }
        Rotor2D operator+(const Rotor2D& r) const { return RotateBy(r); }
        Rotor2D operator-(const Rotor2D& r) const { return RotateByInv(r); }
        Rotor2D operator*(f32 mul) const { return Mul(mul); }
        Rotor2D operator/(f32 div) const { return Mul(1.0f / div); }
        Rotor2D& operator+=(const Rotor2D& r) { return *this = RotateBy(r); }
        Rotor2D& operator-=(const Rotor2D& r) { return *this = RotateByInv(r); }
        Rotor2D& operator*=(f32 mul) { return *this = Mul(mul); }
        Rotor2D& operator/=(f32 div) { return *this = Mul(1.0f / div); }
        fv2 operator*(const fv2& v) const { return Rotate(v); }

        static Rotor2D Random(RandomGenerator& rg);
    };

    template <Numeric T> Vector<T, 2> Vector<T, 2>::RotateBy(const Rotor2D& r) const {
        return r.Rotate(*this);
    }

    template <Numeric T>
    Vector<T, 2> Vector<T, 2>::FromPolar(T r, const Rotor2D& theta) requires Floating<T> {
        const fComplex& t = theta.AsComplex();
        return { t.re * r, t.im * r };
    }

    template <Numeric T>
    Vector<T, 3> Vector<T, 3>::FromSpheric(T r, const Rotor2D& yaw, const Rotor2D& pitch) requires Floating<T> {
        const fComplex& y = yaw.AsComplex(), &p = pitch.AsComplex();
        const float xz = r * p.re;
        return { xz * y.re, r * p.im, xz * y.im };
    }
}
