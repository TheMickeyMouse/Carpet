#include "Rotor3D.h"
#include "Random.h"

namespace Quasi::Math {
    Rotor3D Rotor3D::FromTrig(f32 cosHalf, f32 sinHalf, const fv3& axis) {
        return Quaternion { cosHalf, axis * sinHalf };
    }

    Rotor3D Rotor3D::FromTrig(f32 cosHalf, const fv3& axis) {
        return Quaternion { cosHalf, axis };
    }

    Rotor3D Rotor3D::OrientX(const fv3& xAxis) {
        return Quaternion { xAxis.x, 0, xAxis.z, -xAxis.y };
    }

    Rotor3D Rotor3D::OrientY(const fv3& yAxis) {
        return Quaternion { yAxis.y, -yAxis.z, 0, yAxis.x };
    }

    Rotor3D Rotor3D::OrientZ(const fv3& zAxis) {
        return Quaternion { zAxis.z, zAxis.y, -zAxis.x, 0 };
    }

    fv3 Rotor3D::IHat() const {
        return { 1 - 2 * (y * y + z * z),
                     2 * (x * y + z * w),
                     2 * (x * z - y * w), };
    }
    fv3 Rotor3D::JHat() const {
        return {     2 * (x * y - z * w),
                 1 - 2 * (x * x + z * z),
                     2 * (y * z + x * w), };
    }
    fv3 Rotor3D::KHat() const {
        return {     2 * (x * z + y * w),
                     2 * (y * z - x * w),
                 1 - 2 * (x * x + y * y), };
    }

    Radians Rotor3D::AngleBetween(const Rotor3D& r) const { return Arccos(Dot(r)); }

    Rotor3D Rotor3D::RotateBy(const Rotor3D& r) const {
        // 16 muls, 12 adds
        return AsQuat() * r.AsQuat();
    }
    Rotor3D Rotor3D::RotateByInv(const Rotor3D& r) const {
        // r.xyz signs are flipped
        return Quaternion {
            w * r.w - x * r.x - y * r.y - z * r.z,
            w * r.x + r.w * x + y * r.z - z * r.y,
            w * r.y + r.w * y + z * r.x - x * r.z,
            w * r.z + r.w * z + x * r.y - y * r.x,
        };
    }

    Rotor3D Rotor3D::Halved() const {
        const float u = 1 + w, imul = HALF_ROOT_2 / std::sqrt(u);
        return Quaternion { u * imul, x * imul, y * imul, z * imul };
    }

    Rotor3D Rotor3D::Mul(f32 p) const {
        const f32 angle = std::acos(w), theta = angle * p, sin = std::sin(theta);
        if (sin == 0) return Quaternion { 1, 0, 0, 0 };
        const f32 ratio = sin / std::sin(angle);
        return Quaternion { std::cos(theta), x * ratio, y * ratio, z * ratio };
    }

    Rotor3D Rotor3D::Doubled() const {
        const float w2 = 2 * w;
        return Quaternion { w2 * w - 1, w2 * x, w2 * y, w2 * z };
    }
    Rotor3D Rotor3D::Tripled() const {
        return Doubled() + (*this);
    }
    fv3 Rotor3D::Rotate(const fv3& v) const {
        // 21 mul, 18 adds
        const float xx = x * x, yy = y * y, zz = z * z,
                    xy = x * y, xz = x * z, yz = y * z, xw = x * w, yw = y * w, zw = z * w;
        // [ 1 - 2 * (yy + zz),     2 * (xy - zw),     2 * (xz + yw) ]
        // [     2 * (xy + zw), 1 - 2 * (xx + zz),     2 * (yz - xw) ]
        // [     2 * (xz - yw),     2 * (yz + xw), 1 - 2 * (xx + yy) ]
        return {
            2 * (v.y * (xy - zw) + v.z * (xz + yw) - v.x * (yy + zz)) + v.x,
            2 * (v.x * (xy + zw) + v.z * (yz - xw) - v.y * (xx + zz)) + v.y,
            2 * (v.x * (xz - yw) + v.y * (yz + xw) - v.z * (xx + yy)) + v.z,
        };
    }

    fv3 Rotor3D::InvRotate(const fv3& v) const {
        // 21 mul, 18 adds
        // xyz signs are flipped, but since theyre multiplied by pairs the only
        // sign change is in xw, yw, and zw
        const float xx = x * x, yy = y * y, zz = z * z,
                    xy = x * y, xz = x * z, yz = y * z, xw = x * w, yw = y * w, zw = z * w;
        return {
            2 * (v.y * (xy + zw) + v.z * (xz - yw) - v.x * (yy + zz)) + v.x,
            2 * (v.x * (xy - zw) + v.z * (yz + xw) - v.y * (xx + zz)) + v.y,
            2 * (v.x * (xz + yw) + v.y * (yz - xw) - v.z * (xx + yy)) + v.z,
        };
    }

    Rotor3D Rotor3D::Random(RandomGenerator& rg) {
        const auto [u, v, w] = fv3::Random(rg, 0, 1);
        const f32 uComp = std::sqrt(1 - u), uSqrt = std::sqrt(u);
        return Quaternion {
            uComp * std::sin(TAU * v),
            uComp * std::cos(TAU * v),
            uSqrt * std::sin(TAU * w),
            uSqrt * std::cos(TAU * w)
        };
    }
}