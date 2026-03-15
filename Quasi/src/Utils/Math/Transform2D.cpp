#include "Transform2D.h"

#include "Random.h"
#include "Transform3D.h"

namespace Quasi::Math {
    MatrixTransform2D::MatrixTransform2D(const Matrix2D& m, bool preservesNs)
        : transform(m), normalMatrix(m.As2x2().Inverse().Transpose()), preservesNormals(preservesNs) {}

    MatrixTransform2D::MatrixTransform2D(const Matrix2D& m, const Matrix2x2& nMat, bool preservesNs)
        : transform(m), normalMatrix(nMat), preservesNormals(preservesNs) {}

    MatrixTransform2D MatrixTransform2D::Compose(const MatrixTransform2D& lhs, const MatrixTransform2D& rhs) {
        return { lhs.transform * rhs.transform, lhs.normalMatrix * rhs.normalMatrix, lhs.preservesNormals && rhs.preservesNormals };
    }

    fv2 MatrixTransform2D::MulN(const fv2& n) const {
        fv2 nprime = normalMatrix * n;
        if (!preservesNormals) nprime = nprime.Norm();
        return nprime;
    }

    void Pose2D::Translate(const fv2& p) { pos += p; }
    void Pose2D::Rotate(const Rotor2D& r) { pos = rot * pos; rot += r; }
    void Pose2D::RotateAbout(const Rotor2D& r, const fv2& origin) {
        pos = origin + r.Rotate(pos - origin);
        rot += r;
    }

    fv2 Pose2D::Mul(const fv2& point)         const { return rot * point + pos; }
    fv2 Pose2D::MulInv(const fv2& point)      const { return rot.InvRotate(point - pos); }
    fv2 Pose2D::MulN(const fv2& normal)       const { return rot * normal; }
    fv2 Pose2D::MulInvN(const fv2& normal)    const { return rot.InvRotate(normal); }
    fv2 Pose2D::MulD(const fv2& delta)        const { return MulN(delta); } // theyre equivalent
    fv2 Pose2D::MulInvD(const fv2& delta)     const { return MulInvN(delta); } // theyre equivalent
    Rotor2D Pose2D::MulR(const Rotor2D& r)    const { return rot + r; }
    Rotor2D Pose2D::MulInvR(const Rotor2D& r) const { return r - rot; }
    void Pose2D::Reset() { pos = 0; rot = {}; }
    
    Pose2D Pose2D::ForNormals() const { return { 0, rot }; }
    Matrix2D Pose2D::IntoMatrix() const {
        return Matrix2D::Transform(pos, 1, rot);
    }
    Matrix2x2 Pose2D::IntoMatrixN() const {
        return rot.Inverse().AsMatrixLinear();
    }
    Matrix2x2 Pose2D::IntoMatrixD() const {
        return rot.AsMatrixLinear();
    }

    Pose2D Pose2D::Compose(const Pose2D& lhs, const Pose2D& rhs) {
        return { lhs.pos + lhs.rot * rhs.pos, lhs.rot + rhs.rot };
    }

    Transform2D Transform2D::RotateAbout(const Rotor2D& r, const fv2& origin) {
        return { origin - r.Rotate(origin), 1, r };
    }

    fv2 Transform2D::Mul(const fv2& point)         const { return rot.Rotate(point * scale) + pos; }
    fv2 Transform2D::MulInv(const fv2& point)      const { return rot.InvRotate(point - pos) / scale; }
    fv2 Transform2D::MulN(const fv2& normal)       const { return rot.Rotate(normal / scale).Norm(); }
    fv2 Transform2D::MulInvN(const fv2& normal)    const { return (rot.InvRotate(normal) * scale).Norm(); }
    fv2 Transform2D::MulD(const fv2& delta)        const { return rot.Rotate(delta * scale); }
    fv2 Transform2D::MulInvD(const fv2& delta)     const { return rot.InvRotate(delta) / scale; }
    Rotor2D Transform2D::MulR(const Rotor2D& r)    const { return rot + r; }
    Rotor2D Transform2D::MulInvR(const Rotor2D& r) const { return r - rot; }
    
    void Transform2D::Reset() { pos = 0; scale = 1; rot = {}; }

    Transform2D Transform2D::ForNormalsNonOrtho() const {
        return { 0, 1.0f / scale, rot };
    }

    Matrix2D Transform2D::IntoMatrix() const {
        return Matrix2D::Transform(pos, scale, rot);
    }
    Matrix2x2 Transform2D::IntoMatrixN() const {
        return IntoMatrixD().InvRotScaleTranspose();
    }
    Matrix2x2 Transform2D::IntoMatrixD() const {
        Matrix2x2 mat = rot.AsMatrixLinear();
        mat[0] *= scale.x; mat[1] *= scale.y;
        return mat;
    }
} // Quasi