#pragma once
#include "Rotor3D.h"

namespace Quasi::Math {
    struct MatrixTransform3D {
        Matrix3D transform;
        Matrix3x3 normalMatrix;
        bool preservesNormals = false;

        MatrixTransform3D() = default;
        MatrixTransform3D(const Matrix3D& m, bool preservesNs = false);
        MatrixTransform3D(const Matrix3D& m, const Matrix3x3& nMat, bool preservesNs = false);

        template <class T> requires DistantTo<T, MatrixTransform3D>
        MatrixTransform3D(const T& transform)
            : MatrixTransform3D(transform.IntoMatrix(), transform.IntoMatrixN(), T::PreservesNormals) {}

        static MatrixTransform3D Compose(const MatrixTransform3D& lhs, const MatrixTransform3D& rhs);
        fv3 Mul(const fv3& p) const;
        fv3 MulN(const fv3& n) const;
        fv3 MulD(const fv3& d) const;
        MatrixTransform3D operator*(const MatrixTransform3D& t) const { return Compose(*this, t); }
    };

    // general T * R
    // this IS closed under composition
    struct Pose3D {
        fv3 pos = 0; Rotor3D rot = {};

        void Translate(const fv3& p);
        void Rotate(const Rotor3D& r);
        void RotateAbout(const Rotor3D& r, const fv3& origin);

        fv3 Mul(const fv3& point) const;
        fv3 MulInv(const fv3& point) const;
        fv3 MulN(const fv3& normal) const;
        fv3 MulInvN(const fv3& normal) const;
        fv3 MulD(const fv3& delta) const;
        fv3 MulInvD(const fv3& delta) const;
        Rotor3D MulR(const Rotor3D& r) const;
        Rotor3D MulInvR(const Rotor3D& r) const;

        void Reset();

        Pose3D ForNormals() const;
        Matrix3D  IntoMatrix()  const;
        Matrix3x3 IntoMatrixN() const;
        Matrix3x3 IntoMatrixD() const;
        static constexpr bool PreservesNormals = true;

        static Pose3D Compose(const Pose3D& lhs, const Pose3D& rhs);
        fv3 operator*(const fv3& p) const { return Mul(p); }
        Pose3D operator*(const Pose3D& t) const { return Compose(*this, t); }
    };

    // general T * R * S
    // this class actually isn't closed under composition
    // so if you want to compose them use MatrixTransforms instead
    struct Transform3D {
        fv3 pos = 0, scale = 1;
        Rotor3D rot {};

        static Transform3D RotateAbout(const Rotor3D& r, const fv3& origin);

        fv3 Mul(const fv3& point) const;
        fv3 MulInv(const fv3& point) const;
        fv3 MulN(const fv3& normal) const;
        fv3 MulInvN(const fv3& normal) const;
        fv3 MulD(const fv3& delta) const;
        fv3 MulInvD(const fv3& delta) const;
        Rotor3D MulR(const Rotor3D& r) const;
        Rotor3D MulInvR(const Rotor3D& r) const;

        void Reset();

        // doesnt preserve noraml lengths
        Transform3D ForNormalsNonOrtho() const;
        Matrix3D  IntoMatrix() const;
        Matrix3x3 IntoMatrixN() const;
        Matrix3x3 IntoMatrixD() const;
        static constexpr bool PreservesNormals = false;

        fv3 operator*(const fv3& p) const { return Mul(p); }
    };
} // Quasi
