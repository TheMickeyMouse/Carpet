#pragma once
#include "Rotor2D.h"

namespace Quasi::Math {
    struct MatrixTransform2D {
        Matrix2D transform;
        Matrix2x2 normalMatrix;
        bool preservesNormals = false;
        
        MatrixTransform2D() = default;
        MatrixTransform2D(const Matrix2D& m, bool preservesNs = false);
        MatrixTransform2D(const Matrix2D& m, const Matrix2x2& nMat, bool preservesNs = false);

        template <class T> requires DistantTo<T, MatrixTransform2D>
        MatrixTransform2D(const T& transform)
            : MatrixTransform2D(transform.IntoMatrix(), transform.IntoMatrixN(), T::PreservesNormals) {}

        static MatrixTransform2D Compose(const MatrixTransform2D& lhs, const MatrixTransform2D& rhs);
        fv2 Mul(const fv2& p)  const { return transform * p; }
        fv2 MulN(const fv2& n) const;
        fv2 MulD(const fv2& d) const { return (fv2)(transform * fv3(d.x, d.y, 0)); }
        MatrixTransform2D operator*(const MatrixTransform2D& t) const { return Compose(*this, t); }
    };

    // general T * R
    // this IS closed under composition
    struct Pose2D {
        fv2 pos = 0;
        Rotor2D rot = {};

        void Translate(const fv2& p);
        void Rotate(const Rotor2D& r);
        void RotateAbout(const Rotor2D& r, const fv2& origin);

        fv2 Mul(const fv2& point) const;
        fv2 MulInv(const fv2& point) const;
        fv2 MulN(const fv2& normal) const;
        fv2 MulInvN(const fv2& normal) const;
        fv2 MulD(const fv2& delta) const;
        fv2 MulInvD(const fv2& delta) const;
        Rotor2D MulR(const Rotor2D& r) const;
        Rotor2D MulInvR(const Rotor2D& r) const;

        void Reset();

        Pose2D ForNormals() const;
        Matrix2D  IntoMatrix()  const;
        Matrix2x2 IntoMatrixN() const;
        Matrix2x2 IntoMatrixD() const;
        static constexpr bool PreservesNormals = true;

        static Pose2D Compose(const Pose2D& lhs, const Pose2D& rhs);
        fv2 operator*(const fv2& p) const { return Mul(p); }
        Pose2D operator*(const Pose2D& t) const { return Compose(*this, t); }
    };

    // T * R * S
    // not closed under composition
    struct Transform2D {
        fv2 pos = 0, scale = 1;
        Rotor2D rot {};

        static Transform2D RotateAbout(const Rotor2D& r, const fv2& origin);

        fv2 Mul(const fv2& point) const;
        fv2 MulInv(const fv2& point) const;
        fv2 MulN(const fv2& normal) const;
        fv2 MulInvN(const fv2& normal) const;
        fv2 MulD(const fv2& delta) const;
        fv2 MulInvD(const fv2& delta) const;
        Rotor2D MulR(const Rotor2D& r) const;
        Rotor2D MulInvR(const Rotor2D& r) const;

        void Reset();

        // doesnt preserve noraml lengths
        Transform2D ForNormalsNonOrtho() const;
        Matrix2D  IntoMatrix() const;
        Matrix2x2 IntoMatrixN() const;
        Matrix2x2 IntoMatrixD() const;
        static constexpr bool PreservesNormals = false;

        fv2 operator*(const fv2& p) const { return Mul(p); }
    };
    template <Numeric T> Vector<T, 2> Vector<T, 2>::TransformBy(const Transform2D& t) const {
        return t.Mul(*this);
    }
} // Quasi
