#include "Matrix.h"

#include <xmmintrin.h>

#include "Transform2D.h"
#include "Transform3D.h"

namespace Quasi::Math {
    Matrix<2> Matrix<2>::RotationLin(const Rotor2D& rotation) {
        return rotation.AsMatrixLinear();
    }

    Matrix<2>& Matrix<2>::RotateByLin(const Rotor2D& rotation) {
        const fComplex& z = rotation.AsComplex();
        float* m = &unitVectors[0][0];
        const float arr[4] = { m[0] * z.re - m[1] * z.im,
                               m[0] * z.im + m[1] * z.re,
                               m[2] * z.re - m[3] * z.im,
                               m[2] * z.im + m[3] * z.re };
        Memory::MemCopy(m, arr, sizeof(arr));
        return *this;
    }

    Rotor2D Matrix<2>::GetRotationLin() const {
        return Rotor2D::FromComplex(fComplex::FromVec2D(unitVectors[0]));
    }

    Matrix<3> Matrix<3>::Rotation(const Rotor2D& rotation) {
        return rotation.AsMatrix();
    }

    Matrix<3>& Matrix<3>::RotateBy(const Rotor2D& rotation) {
        const fComplex& z = rotation.AsComplex();
        float* m = &unitVectors[0][0];
        const float arr[4] = { m[0] * z.re - m[1] * z.im,
                               m[0] * z.im + m[1] * z.re,
                               m[3] * z.re - m[4] * z.im,
                               m[3] * z.im + m[4] * z.re };
        m[0] = arr[0];
        m[1] = arr[1];
        m[3] = arr[2];
        m[4] = arr[3];
        return *this;
    }

    Rotor2D Matrix<3>::GetRotation() const {
        return Rotor2D::FromComplex(fComplex::FromVec2D(unitVectors[0].As2D()));
    }

    Matrix<3> Matrix<3>::RotationLin(const Rotor3D& rotation) {
        return rotation.AsMatrixLinear();
    }

    Matrix<3>& Matrix<3>::RotateByLin(const Rotor3D& rotation) {
        const Matrix3x3 matrixForm = rotation.AsMatrixLinear();
        const fv3 columns[3] = { matrixForm * unitVectors[0],
                                 matrixForm * unitVectors[1],
                                 matrixForm * unitVectors[2] };
        Memory::MemCopy(&unitVectors, &columns, sizeof(columns));
        return *this;
    }

    Rotor3D Matrix<3>::GetRotationLin() const {
        const float* m = &unitVectors[0][0];
        float trace;
        Quaternion q;
        if (m[8] < 0) {
            if (m[0] > m[4]) {
                trace = 1 + m[0] - m[4] - m[8];
                q = { trace, m[1] + m[3], m[2] + m[6], m[7] - m[5] };
            } else {
                trace = 1 - m[0] + m[4] - m[8];
                q = { m[1] + m[3], trace, m[5] + m[7], m[2] - m[6] };
            }
        } else {
            if (m[0] < -m[4]) {
                trace = 1 - m[0] - m[4] + m[8];
                q = { m[2] + m[6], m[5] + m[7], trace, m[3] - m[1] };
            } else {
                trace = 1 + m[0] + m[4] + m[8];
                q = { m[7] - m[5], m[2] - m[6], m[3] - m[1], trace };
            }
        }
        q *= 0.5f / std::sqrt(trace);
        return Rotor3D::FromQuat(q);
    }

    Matrix<2> Matrix<3, 3>::As2x2() const {
        const auto& m = *this;
        return Matrix2x2::FromColumnMatrix({ m[0][0], m[0][1], m[1][0], m[1][1] });
    }

    MatrixTransform2D Matrix<3, 3>::AsTransform() const {
        const Matrix2x2 sub = As2x2();
        return { *this, sub.Inverse() };
    }

    Matrix<3> Matrix<3>::Transform(const fv2& translate, const fv2& scale, const Rotor2D& rotate) {
        Matrix m = rotate.AsMatrix();
        m[0] *= scale.x;
        m[1] *= scale.y;
        m[2] = translate.AddZ(1);
        return m;
    }

    Matrix<4> Matrix<4>::Transpose() const {
        // https://stackoverflow.com/a/16743203
        Matrix result { Uninit };
        __m128 row1 = _mm_load_ps(&unitVectors[0][0]);
        __m128 row2 = _mm_load_ps(&unitVectors[1][0]);
        __m128 row3 = _mm_load_ps(&unitVectors[2][0]);
        __m128 row4 = _mm_load_ps(&unitVectors[3][0]);
        _MM_TRANSPOSE4_PS(row1, row2, row3, row4);
        _mm_store_ps(&result.unitVectors[0][0], row1);
        _mm_store_ps(&result.unitVectors[1][0], row2);
        _mm_store_ps(&result.unitVectors[2][0], row3);
        _mm_store_ps(&result.unitVectors[3][0], row4);
        return result;
    }

    Matrix<4> Matrix<4>::Rotation(const Rotor3D& rotation) {
        return rotation.AsMatrix();
    }

    Matrix<4>& Matrix<4>::RotateBy(const Rotor3D& rotation) {
        const Matrix3x3 matrixForm = rotation.AsMatrixLinear();
        const fv4 columns[3] = { (fv4)(matrixForm * unitVectors[0].As3D()),
                                 (fv4)(matrixForm * unitVectors[1].As3D()),
                                 (fv4)(matrixForm * unitVectors[2].As3D()) };
        Memory::MemCopy(&unitVectors, &columns, sizeof(columns));
        return *this;
    }

    Rotor3D Matrix<4>::GetRotation() const {
        const float* m = &unitVectors[0][0];
        float trace;
        Quaternion q;
        if (m[10] < 0) {
            if (m[0] > m[5]) {
                trace = 1 + m[0] - m[5] - m[10];
                q = { trace, m[1] + m[4], m[2] + m[8], m[9] - m[6] };
            } else {
                trace = 1 - m[0] + m[5] - m[10];
                q = { m[1] + m[4], trace, m[6] + m[9], m[2] - m[8] };
            }
        } else {
            if (m[0] < -m[5]) {
                trace = 1 - m[0] - m[5] + m[10];
                q = { m[2] + m[8], m[6] + m[9], trace, m[4] - m[1] };
            } else {
                trace = 1 + m[0] + m[5] + m[10];
                q = { m[9] - m[6], m[2] - m[8], m[4] - m[1], trace };
            }
        }
        q *= 0.5f / std::sqrt(trace);
        return Rotor3D::FromQuat(q);
    }

    Matrix<3> Matrix<4, 4>::As3x3() const {
        const auto& m = *this;
        return Matrix3x3::FromColumnMatrix({ m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2] });
    }

    MatrixTransform3D Matrix<4, 4>::AsTransform() const {
        const Matrix3x3 sub = As3x3();
        return { *this, sub.Inverse() };
    }

    Matrix<4> Matrix<4>::OrthoProjection(const fRect3D& box) {
        // a bit of explaination: (dx is diff, sx is sum)
        // [ 2 / dx ,   0    ,    0    , -sx / dx ]
        // [   0    , 2 / dy ,    0    , -sy / dy ]
        // [   0    ,   0    , -2 / dz , -sz / dz ]
        // [   0    ,   0    ,    0    ,     1    ]
        const float rdx = 1 / box.Width(),  sx = box.min.x + box.max.x,
                    rdy = 1 / box.Height(), sy = box.min.y + box.max.y,
                    rdz = 1 / box.Depth(),  sz = box.min.z + box.max.z;
        return {{
            2 * rdx, 0, 0, -sx * rdx,
            0, 2 * rdy, 0, -sy * rdy,
            0, 0, 2 * rdz, -sz * rdz,
            0, 0, 0,        1
        }};
    }

    Matrix<4> Matrix<4>::PerspectiveProjection(const fRect3D& box) {
        // heres the math: http://www.songho.ca/opengl/gl_projectionMatrix.html
        // (dx is diff, sx is sum), n is near, f is far
        // { 2 * n / dx ,     0      ,  sx / dx ,       0         }
        // {     0      , 2 * n / dy ,  sy / dy ,       0         }
        // {     0      ,     0      , -sz / dz , -2 * n * f / dz }
        // {     0      ,     0      ,    -1    ,       0         }
        const float rdx = 1 / box.Width(),  sx = box.min.x + box.max.x,
                    rdy = 1 / box.Height(), sy = box.min.y + box.max.y,
                    rdz = 1 / box.Depth(),  sz = box.min.z + box.max.z,
                    n = box.min.z, f = box.max.z;
        return {{
            2 * n * rdx, 0,  sx * rdx,  0,
            0, 2 * n * rdy,  sy * rdy,  0,
            0, 0,           -sz * rdz, -2 * n * f * rdz,
            0, 0,           -1,         0,
        }};
    }

    Matrix<4> Matrix<4>::PerspectiveFov(Radians fovDeg, float aspect, float near, float far) {
        const float tan   = Math::Tan(fovDeg * 0.5f),
                    y     = 1.0f /  tan,
                    x     = 1.0f / (tan * aspect),
                    rdz   = 1.0f / (far - near),
                    zsum  = (far + near) * rdz,
                    zprod = (far * near) * rdz;
        return {{
            x, 0,  0,    0,
            0, y,  0,    0,
            0, 0, -zsum, -2 * zprod,
            0, 0, -1,    0
        }};
    }

    Matrix<4> Matrix<4>::Transform(const fv3& translate, const fv3& scale, const Rotor3D& rotate) {
        Matrix m = rotate.AsMatrix();
        m[0] *= scale.x;
        m[1] *= scale.y;
        m[2] *= scale.z;
        m[3] = translate.AddW(1);
        return m;
    }

    Matrix<4> Matrix<4>::LookAt(const fv3& eye, const fv3& direction, const fv3& worldUp) {
        // from this answer: https://stackoverflow.com/a/21830596
        // z is front
        // getting the vector perpendicular to the plane (eye -> center) and worldUp
        const fv3 viewX = direction.Cross(worldUp).Norm();
        // getting localUp from viewX and viewZ
        const fv3 viewY = viewX.Cross(direction);
        return {{
             viewX.x,      viewX.y,      viewX.z,     -viewX    .Dot(eye),
             viewY.x,      viewY.y,      viewY.z,     -viewY    .Dot(eye),
            -direction.x, -direction.y, -direction.z,  direction.Dot(eye),
             0,            0,            0,            1,
        }};
    }
}
