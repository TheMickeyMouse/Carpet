#pragma once
#include "Transform2D.h"

namespace Quasi::Math {
    template <class> struct Complex;
    using fComplex = Complex<float>;

    struct Quaternion {
        f32 w, x, y, z;

        Quaternion(float w = 1) : w(w), x(0), y(0), z(0) {}
        Quaternion(f32 w, f32 x, f32 y, f32 z) : w(w), x(x), y(y), z(z) {}
        Quaternion(f32 w, const fv3& xyz) : w(w), x(xyz.x), y(xyz.y), z(xyz.z) {}
        Quaternion(f32 x, f32 y, f32 z) : w(0), x(x), y(y), z(z) {}
        Quaternion(const fv3& xyz) : Quaternion(xyz.x, xyz.y, xyz.z) {}

        fv3 GetXYZ()  const { return { x, y, z }; }
        fv4 GetWXYZ() const { return { w, x, y, z }; }

        static constexpr Str ROTATION_ORDER = "ZYX"; // readonly property thats not used

        static Quaternion From4D(const fv4& q) { return { q.w, q.x, q.y, q.z }; }
        static Quaternion From3D(const fv3& q) { return { 0,   q.x, q.y, q.z }; }
        static Quaternion FromWXYZ(float w, float x, float y, float z) { return { w, x, y, z }; }

        static Quaternion RotateAxis(const fv3& axis, const Rotor2D& rotation); // assumes normalized axis
        static Quaternion RotateX(const Rotor2D& r);
        static Quaternion RotateY(const Rotor2D& r);
        static Quaternion RotateZ(const Rotor2D& r);
        static Quaternion RotateXYZ(const Vec3<Rotor2D>& r);
        static Quaternion RotateTo(const fv3& from, const fv3& to); // both vectors assumed to be normed

        static Quaternion FromEulerAngles(const Vec3<Rotor2D>& r) { return RotateXYZ(r); }
        Vec3<Radians> ToEulerAngles() const;

        static Quaternion LookAt(const fv3& direction, const fv3& worldFront); // both vectors assumed to be normed

        Matrix3x3 AsMatrixLinear() const;
        Matrix3D  AsMatrix() const;
        Matrix4x4 AsComputeMatrix() const;

        f32 LenSq() const;
        f32 Len() const;
        f32 Abs() const;
        f32 DistSq(const Quaternion& q) const;
        f32 Dist(const Quaternion& q) const;
        f32 Dot(const Quaternion& q) const;
        Quaternion Norm() const;

        Quaternion Exp() const;
        Quaternion Log() const;
        Quaternion Pow(f32 p) const;

        Quaternion operator+() const { return *this; }
        Quaternion operator-() const { return { -w, -x, -y, -z }; }
        Quaternion Conj() const;
        Quaternion Inv() const;

        Quaternion MulI() const;
        Quaternion MulJ() const;
        Quaternion MulK() const;

        Quaternion Lerp (const Quaternion& q, f32 t) const;
        Quaternion Slerp(const Quaternion& q, f32 t) const;
        Quaternion Slerp(const Quaternion& q, f32 t, int revolutions) const;

        Quaternion operator+(const Quaternion& q) const;
        Quaternion operator-(const Quaternion& q) const;
        Quaternion operator*(f32 v) const;
        Quaternion operator/(f32 v) const;
        Quaternion operator*(const Quaternion& q) const;
        Quaternion operator/(const Quaternion& q) const;
        Quaternion& operator+=(const Quaternion& q);
        Quaternion& operator-=(const Quaternion& q);
        Quaternion& operator*=(f32 v);
        Quaternion& operator*=(const Quaternion& q);
        Quaternion& operator/=(f32 v);
        Quaternion& operator/=(const Quaternion& q);
    };

    Quaternion operator+(f32 w, const Quaternion& q);
    Quaternion operator-(f32 w, const Quaternion& q);
    Quaternion operator*(f32 w, const Quaternion& q);
    Quaternion operator/(f32 w, const Quaternion& q);

    inline Quaternion operator""_qi(long double i) { return Quaternion::FromWXYZ(0, (float)i, 0, 0); }
    inline Quaternion operator""_qj(long double j) { return Quaternion::FromWXYZ(0, 0, (float)j, 0); }
    inline Quaternion operator""_qk(long double k) { return Quaternion::FromWXYZ(0, 0, 0, (float)k); }
} // Quasi
