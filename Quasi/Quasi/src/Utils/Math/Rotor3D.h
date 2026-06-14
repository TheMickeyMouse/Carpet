#pragma once
#include "Quaternion.h"

namespace Quasi::Math {
    struct Rotor3D : private Quaternion {
        Rotor3D() = default;
        Rotor3D(Radians x, Radians y, Radians z) : Quaternion(FromEulerAngles({ x, y, z })) {}
        Rotor3D(const Rotor2D& x, const Rotor2D& y, const Rotor2D& z) : Quaternion(FromEulerAngles({ x, y, z })) {}
    private:
        Rotor3D(const Quaternion& q) : Quaternion(q) {}
    public:
        static Rotor3D  FromQuat(const Quaternion& c) { return { c }; }
        Quaternion&       AsQuat()       { return static_cast<Quaternion&>(*this); }
        const Quaternion& AsQuat() const { return static_cast<const Quaternion&>(*this); }

        static Rotor3D FromTrig(f32 cosHalf, f32 sinHalf, const fv3& axis);
        static Rotor3D FromTrig(f32 cosHalf, const fv3& axis);
        static Rotor3D RotateAxis(const fv3& axis, const Rotor2D& r) { return Quaternion::RotateAxis(axis, r); }
        static Rotor3D LookAt(const fv3& direction, const fv3& front) { return Quaternion::LookAt(direction, front); }
        static Rotor3D RotateTo(const fv3& from, const fv3& to) { return Quaternion::RotateTo(from, to); }
        static Rotor3D RotateX(const Rotor2D& r) { return Quaternion::RotateX(r); }
        static Rotor3D RotateY(const Rotor2D& r) { return Quaternion::RotateY(r); }
        static Rotor3D RotateZ(const Rotor2D& r) { return Quaternion::RotateZ(r); }
        static Rotor3D OrientX(const fv3& xAxis);
        static Rotor3D OrientY(const fv3& yAxis);
        static Rotor3D OrientZ(const fv3& zAxis);

        fv3 IHat() const;
        fv3 JHat() const;
        fv3 KHat() const;
        f32 CosHalf() const { return w; }
        f32 SinHalf() const { return std::sqrt(1 - w * w); }
        fv3 Axis() const { return { x, y, z }; }

        Vec3<Radians> EulerAngles() const { return ToEulerAngles(); }
        Radians AngleBetween(const Rotor3D& r) const;

        Rotor3D RotateBy   (const Rotor3D& r) const;
        Rotor3D RotateByInv(const Rotor3D& r) const;

        Rotor3D Halved() const;
        Rotor3D Mul(f32 p) const;
        Rotor3D Doubled()  const;
        Rotor3D Tripled()  const;
        Rotor3D Inverse()  const { return Conj(); }

        Matrix3x3 AsMatrixLinear() const { return AsQuat().AsMatrixLinear(); }
        Matrix3D  AsMatrix()       const { return AsQuat().AsMatrix(); }
        fv3 Rotate   (const fv3& v) const;
        fv3 InvRotate(const fv3& v) const;

        Rotor3D Lerp(const Rotor3D& z, f32 t) const { return AsQuat().Slerp(z, t); }
        Rotor3D Lerp(const Rotor3D& z, f32 t, int revolutions) const { return AsQuat().Slerp(z, t, revolutions); }

        Rotor3D operator+() const { return *this; }
        Rotor3D operator-() const { return Inverse(); }
        Rotor3D operator+(const Rotor3D& r) const { return RotateBy(r); }
        Rotor3D operator-(const Rotor3D& r) const { return RotateByInv(r); }
        Rotor3D operator*(f32 mul) const { return Mul(mul); }
        Rotor3D operator/(f32 div) const { return Mul(1.0f / div); }
        Rotor3D& operator+=(const Rotor3D& r) { return *this = RotateBy(r); }
        Rotor3D& operator-=(const Rotor3D& r) { return *this = RotateByInv(r); }
        Rotor3D& operator*=(f32 mul) { return *this = Mul(mul); }
        Rotor3D& operator/=(f32 div) { return *this = Mul(1.0f / div); }
        fv3 operator*(const fv3& v) const { return Rotate(v); }

        static Rotor3D Random(RandomGenerator& rg);
    };
}
