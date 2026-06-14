#include "Transform3D.h"

namespace Quasi::Math {
    MatrixTransform3D::MatrixTransform3D(const Matrix3D& m, bool preservesNs)
        : transform(m), normalMatrix(m.As3x3().Inverse().Transpose()), preservesNormals(preservesNs) {}

    MatrixTransform3D::MatrixTransform3D(const Matrix3D& m, const Matrix3x3& nMat, bool preservesNs)
        : transform(m), normalMatrix(nMat), preservesNormals(preservesNs) {}

    MatrixTransform3D MatrixTransform3D::Compose(const MatrixTransform3D& lhs, const MatrixTransform3D& rhs) {
        return { lhs.transform * rhs.transform, lhs.normalMatrix * rhs.normalMatrix, lhs.preservesNormals && rhs.preservesNormals };
    }

    fv3 MatrixTransform3D::Mul(const fv3& p) const {
        return transform * p;
    }

    fv3 MatrixTransform3D::MulN(const fv3& n) const {
        fv3 nprime = normalMatrix * n;
        if (!preservesNormals) nprime = nprime.Norm();
        return nprime;
    }

    fv3 MatrixTransform3D::MulD(const fv3& d) const {
        return (transform * fv4(d, 0)).As3D();
    }

    void Pose3D::Translate(const fv3& p) { pos += p; }
    void Pose3D::Rotate(const Rotor3D& r) { pos = rot.Rotate(pos); rot += r; }
    void Pose3D::RotateAbout(const Rotor3D& r, const fv3& origin) {
        pos = origin + r.Rotate(pos - origin);
        rot = r + rot;
    }

    fv3 Pose3D::Mul(const fv3& point)         const { return rot.Rotate(point) + pos; }
    fv3 Pose3D::MulInv(const fv3& point)      const { return rot.InvRotate(point - pos); }
    fv3 Pose3D::MulN(const fv3& normal)       const { return rot.Rotate(normal); }
    fv3 Pose3D::MulInvN(const fv3& normal)    const { return rot.InvRotate(normal); }
    fv3 Pose3D::MulD(const fv3& delta)        const { return MulN(delta); } // theyre equivalent
    fv3 Pose3D::MulInvD(const fv3& delta)     const { return MulInvN(delta); } // theyre equivalent
    Rotor3D Pose3D::MulR(const Rotor3D& r)    const { return rot + r; }
    Rotor3D Pose3D::MulInvR(const Rotor3D& r) const { return r - rot; }
    void Pose3D::Reset() { pos = 0; rot = {}; }

    Pose3D Pose3D::ForNormals() const { return { 0, rot }; }
    Matrix3D Pose3D::IntoMatrix() const {
        return Matrix3D::Transform(pos, 1, rot);
    }
    Matrix3x3 Pose3D::IntoMatrixN() const {
        return rot.Inverse().AsMatrixLinear();
    }
    Matrix3x3 Pose3D::IntoMatrixD() const {
        return rot.AsMatrixLinear();
    }

    Pose3D Pose3D::Compose(const Pose3D& lhs, const Pose3D& rhs) {
        return { lhs.pos + lhs.rot * rhs.pos, lhs.rot + rhs.rot };
    }

    Transform3D Transform3D::RotateAbout(const Rotor3D& r, const fv3& origin) {
        return { origin - r.Rotate(origin), 1, r };
    }
    fv3 Transform3D::Mul(const fv3& point)         const { return rot.Rotate(point * scale) + pos; }
    fv3 Transform3D::MulInv(const fv3& point)      const { return rot.InvRotate(point - pos) / scale; }
    fv3 Transform3D::MulN(const fv3& normal)       const { return rot.Rotate(normal / scale).Norm(); }
    fv3 Transform3D::MulInvN(const fv3& normal)    const { return (rot.InvRotate(normal) * scale).Norm(); }
    fv3 Transform3D::MulD(const fv3& delta)        const { return rot.Rotate(delta * scale); }
    fv3 Transform3D::MulInvD(const fv3& delta)     const { return rot.InvRotate(delta) / scale; }
    Rotor3D Transform3D::MulR(const Rotor3D& r)    const { return rot + r; }
    Rotor3D Transform3D::MulInvR(const Rotor3D& r) const { return r - rot; }

    void Transform3D::Reset() {
        pos = 0;
        scale = 1;
        rot = {};
    }

    Transform3D Transform3D::ForNormalsNonOrtho() const {
        return { 0, 1.0f / scale, rot };
    }

    Matrix3D Transform3D::IntoMatrix() const {
        return Matrix3D::Transform(pos, scale, rot);
    }
    Matrix3x3 Transform3D::IntoMatrixN() const {
        return IntoMatrixD().InvRotScaleTranspose();
    }
    Matrix3x3 Transform3D::IntoMatrixD() const {
        Matrix3x3 mat = rot.AsMatrixLinear();
        mat[0] *= scale.x; mat[1] *= scale.y; mat[2] *= scale.z;
        return mat;
    }
} // Quasi