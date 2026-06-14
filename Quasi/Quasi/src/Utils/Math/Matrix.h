#pragma once
#include "Rect.h"

namespace Quasi::Math {
    struct MatrixTransform2D;
    struct MatrixTransform3D;
}

namespace Quasi::Math {
    struct Rotor3D;
    template <usize N, usize M = N> struct Matrix;

    template <usize N, usize M> // N is the dimension of each vector, M is the number of vectors
    struct IMatrix {
        using Column    = Vector<float, N>;
        using ColumnAff = Vector<float, N - 1>;
        using Row       = Vector<float, M>;
        using RowAff    = Vector<float, M - 1>;
        using Super     = Matrix<N, M>;
        Vector<float, N> unitVectors[M];

        static constexpr bool SquareMatrix = N == M;
    private:
        void ConstructIdentity() requires SquareMatrix {
            for (usize i = 0; i < N; ++i) { unitVectors[i][i] = 1.0f; }
        }
        Super& super() { return static_cast<Super&>(*this); }
        const Super& super() const { return static_cast<const Super&>(*this); }
    public:
        IMatrix() requires SquareMatrix { ConstructIdentity(); }
        IMatrix(UninitMarker) {} // the uninitialized initializer
        IMatrix(const float (&values) [N * M]) { CopyTransposed(values); }

        void CopyTransposed(Span<const float> transposedData) {
            for (usize i = 0; i < M; ++i)
                for (usize j = 0; j < N; j++)
                    unitVectors[i][j] = transposedData[j * M + i];
        }

        static Super FromColumns(const Column (&units)[M]) {
            Super mat { Uninit };
            Memory::MemCopy(&mat.unitVectors[0], units, N * M * sizeof(float));
            return mat;
        }
        static Super Identity() requires SquareMatrix { return Super {}; }
        static Super Zero() { return Super { Uninit }; }
        static Super FromColumnMatrix(const float (&entries)[N * M]) {
            Super mat { Uninit };
            Memory::MemCopy(&mat.unitVectors[0], entries, N * M * sizeof(float));
            return mat;
        }
        static Super FromRowMatrix(const float (&entries)[N * M]) {
            Super mat { Uninit };
            mat.CopyTransposed(Spans::Slice(entries, N * M));
            return mat;
        }

        const float* Data() const { return &unitVectors[0][0]; }
        float* Data() { return &unitVectors[0][0]; }
        Span<const float> AsSpan() const { return Spans::Slice(&unitVectors[0][0], N * M); }
        Span<const Vector<float, N>> Columns() const { return Spans::Slice(unitVectors, M); }

        static Super Translation(const ColumnAff& translation) {
            Super t;
            t[M - 1] = translation.AddComponent(1);
            return t;
        }
        Super& TranslateBy(const ColumnAff& translation) {
            unitVectors[M - 1] += translation;
            return super();
        }
        ColumnAff GetTranslation() const { return unitVectors[M - 1].RemoveComponent(); }
        static Super Scaling(const ColumnAff& scale) requires SquareMatrix { return ScalingLinear(scale.AddComponent(1)); }
        static Super ScalingLinear(const Column& scale) requires SquareMatrix {
            Super t = { Uninit };
            for (usize i = 0; i < M; ++i)
                t.unitVectors[i][i] = scale[i];
            return t;
        }
        Super& ScaleBy(const ColumnAff& scale) { return ScaleByLinear(scale.AddComponent(1)); }
        Super& ScaleByLinear(const Column& scale) {
            for (usize i = 0; i < M; ++i)
                unitVectors[i] *= scale[i];
            return super();
        }
        ColumnAff GetScaleSq() const requires SquareMatrix {
            ColumnAff scaleSq;
            for (usize i = 0; i < M; ++i) {
                for (usize j = 0; j < N - 1; ++j)
                    scaleSq[j] += unitVectors[i][j] * unitVectors[i][j];
            }
            return scaleSq;
        }
        Column GetScaleLinearSq() const requires SquareMatrix {
            Column scaleSq;
            for (usize i = 0; i < M; ++i) {
                for (usize j = 0; j < N; ++j)
                    scaleSq[j] += unitVectors[i][j] * unitVectors[i][j];
            }
            return scaleSq;
        }
        ColumnAff GetScale() const requires SquareMatrix { return GetScaleSq().Map(Qfn$(std::sqrt)); }

        Matrix<M, N> Transpose() const {
            Matrix<M, N> transposed;
            for (usize i = 0; i < M; ++i)
                for (usize j = 0; j < N; ++j)
                    transposed[j][i] = unitVectors[i][j];
            return transposed;
        }
        float Det() const requires SquareMatrix { // determinate
            const float* m = &unitVectors[0][0];
            if constexpr (N == 2) {
                return m[0] * m[3] - m[1] * m[2];
            } else if constexpr (N == 3) {
                return m[0] * (m[4] * m[8] - m[5] * m[7])
                     - m[1] * (m[3] * m[8] - m[5] * m[6])
                     + m[2] * (m[3] * m[7] - m[4] * m[6]);
            } else if constexpr (N == 4) {
                // 28 multiplications, 17 additions
                const float m2x2[] {
                    m[10] * m[15] - m[11] * m[14], // remove 0, 1 -> [0]
                    m[ 9] * m[15] - m[11] * m[13], // remove 0, 2 -> [1]
                    m[ 9] * m[14] - m[10] * m[13], // remove 0, 3 -> [2]
                    m[ 8] * m[15] - m[11] * m[12], // remove 1, 2 -> [3]
                    m[ 8] * m[14] - m[10] * m[12], // remove 1, 3 -> [4]
                    m[ 8] * m[13] - m[ 9] * m[12], // remove 2, 3 -> [5]
                };
                return m[0] * (m[5] * m2x2[0] + m[6] * m2x2[1] + m[7] * m2x2[2])
                     - m[1] * (m[4] * m2x2[0] - m[6] * m2x2[3] - m[7] * m2x2[4])
                     + m[2] * (m[7] * m2x2[5] - m[4] * m2x2[1] - m[5] * m2x2[3])
                     - m[3] * (m[4] * m2x2[2] + m[5] * m2x2[4] + m[6] * m2x2[5]);
            } else {
                static_assert(true, "not implemented yet. use gaussian elimination or smth");
                return f32s::NAN;
            }
        }

        Super Inverse() const requires SquareMatrix {
            const float* m = &unitVectors[0][0];
            if constexpr (N == 2) {
                const float invDet = 1.0f / Det();
                return {{ m[3] * invDet, -m[2] * invDet,
                          m[1] * invDet,  m[0] * invDet, }};
            } else if constexpr (N == 3) {
                const float m2x2[3] {
                    m[4] * m[8] - m[5] * m[7], // 0, 0
                    m[3] * m[8] - m[5] * m[6], // 0, 1
                    m[3] * m[7] - m[4] * m[6], // 0, 2
                };
                const float invDet = 1.0f / (m[0] * m2x2[0] - m[1] * m2x2[1] + m[2] * m2x2[2]);
                return {{ m2x2[0] * invDet,                     -m2x2[1] * invDet,                      m2x2[2] * invDet,
                         -(m[1] * m[8] - m[2] * m[7]) * invDet,  (m[0] * m[8] - m[2] * m[6]) * invDet, -(m[0] * m[7] - m[1] * m[6]) * invDet,
                          (m[1] * m[5] - m[2] * m[4]) * invDet, -(m[0] * m[5] - m[2] * m[3]) * invDet,  (m[0] * m[4] - m[1] * m[3]) * invDet }};
            } else if constexpr (N == 4) {
                // 104 multiplications, 50 additions
                // these values are generated by a python script lol
                const float m2x2[] {
                    m[10] * m[15] - m[11] * m[14],
                    m[9]  * m[15] - m[11] * m[13],
                    m[9]  * m[14] - m[10] * m[13],
                    m[8]  * m[15] - m[11] * m[12],
                    m[8]  * m[14] - m[10] * m[12],
                    m[8]  * m[13] - m[9]  * m[12],
                    m[6]  * m[15] - m[7]  * m[14],
                    m[5]  * m[15] - m[7]  * m[13],
                    m[5]  * m[14] - m[6]  * m[13],
                    m[4]  * m[15] - m[7]  * m[12],
                    m[4]  * m[14] - m[6]  * m[12],
                    m[4]  * m[13] - m[5]  * m[12],
                    m[6]  * m[11] - m[7]  * m[10],
                    m[5]  * m[11] - m[7]  * m[9],
                    m[5]  * m[10] - m[6]  * m[9],
                    m[4]  * m[11] - m[7]  * m[8],
                    m[4]  * m[10] - m[6]  * m[8],
                    m[4]  * m[9]  - m[5]  * m[8]
                };
                const float m3x3[4] {
                    m[5] * m2x2[0] - m[6] * m2x2[1] + m[7] * m2x2[2], // remove (0, 0)
                    m[4] * m2x2[0] - m[6] * m2x2[3] + m[7] * m2x2[4], // remove (0, 1)
                    m[4] * m2x2[1] - m[5] * m2x2[3] + m[7] * m2x2[5], // remove (0, 2)
                    m[4] * m2x2[2] - m[5] * m2x2[4] + m[6] * m2x2[5], // remove (0, 3)
                };
                const float invdet = 1.0f / (m[0] * m3x3[0] - m[1] * m3x3[1] + m[2] * m3x3[2] - m[3] * m3x3[3]);
                return {{
                   +m3x3[0]                                               * invdet, -m3x3[1]                                               * invdet, +m3x3[2]                                               * invdet, -m3x3[3]                                               * invdet,
                   -(m[1] * m2x2[0]  - m[2] * m2x2[1]  + m[3] * m2x2[2])  * invdet, +(m[0] * m2x2[0]  - m[2] * m2x2[3]  + m[3] * m2x2[4])  * invdet, -(m[0] * m2x2[1]  - m[1] * m2x2[3]  + m[3] * m2x2[5])  * invdet, +(m[0] * m2x2[2]  - m[1] * m2x2[4]  + m[2] * m2x2[5])  * invdet,
                   +(m[1] * m2x2[6]  - m[2] * m2x2[7]  + m[3] * m2x2[8])  * invdet, -(m[0] * m2x2[6]  - m[2] * m2x2[9]  + m[3] * m2x2[10]) * invdet, +(m[0] * m2x2[7]  - m[1] * m2x2[9]  + m[3] * m2x2[11]) * invdet, -(m[0] * m2x2[8]  - m[1] * m2x2[10] + m[2] * m2x2[11]) * invdet,
                   -(m[1] * m2x2[12] - m[2] * m2x2[13] + m[3] * m2x2[14]) * invdet, +(m[0] * m2x2[12] - m[2] * m2x2[15] + m[3] * m2x2[16]) * invdet, -(m[0] * m2x2[13] - m[1] * m2x2[15] + m[3] * m2x2[17]) * invdet, +(m[0] * m2x2[14] - m[1] * m2x2[16] + m[2] * m2x2[17]) * invdet
                }};
            } else {
                static_assert(true, "not implemented yet. use gaussian elimination or smth");
                return f32s::NAN;
            }
        }
        // assumes a linear rotation (linear vs affine doesnt matter). equivalent a transpose
        Super InvRot() const requires SquareMatrix { return Transpose(); }
        // assumes the matrix has only rotation and scaling elements (linear vs affine doesnt matter)
        // and calculates the inverse (much faster than the naive method)
        Super InvRotScale() const requires SquareMatrix {
            return InvRotScaleTranspose().Transpose();
        }
        Super InvRotScaleTranspose() const requires SquareMatrix {
            Column scaleSq = GetScaleLinearSq();
            Super inv = super();
            for (usize i = 0; i < M; ++i)
                inv.unitVectors[i] *= 1 / scaleSq[i];
            return inv;
        }
        // assumes the matrix has only rotation and translation elements
        Super InvTransRot() const requires SquareMatrix {
            // https://math.stackexchange.com/questions/1234948/inverse-of-a-rigid-transformation
            Super inv { Uninit };
            // transpose rotation part
            for (usize i = 0; i < M - 1; ++i)
                for (usize j = 0; j < N - 1; ++j)
                    inv.unitVectors[j][i] = unitVectors[i][j];

            for (usize i = 0; i < N - 1; ++i)
                for (usize j = 0; j < N - 1; ++j)
                    inv.unitVectors[M - 1][i] -= unitVectors[i][j] * unitVectors[N - 1][j];
            inv[M - 1][N - 1] = 1.0f;
            return inv;
        }
        // assumes the matrix is a standard affine transformation matrix (TRS)
        Super InvTRS() const requires SquareMatrix {
            // let A = [ R t ] * [ S 0 ]
            //         [ 0 1 ]   [ 0 1 ]
            // A'    = [ S' 0 ] * [ R^T -R^T . t ]
            //         [ 0  1 ]   [ 0    1       ]
            //       = [ S' R^T -S' (R^T . t) ]
            //         [ 0       1            ]
            Super inv { Uninit };
            const ColumnAff invScaleSq = 1.0f / GetScaleSq();
            // transpose rotation part
            for (usize i = 0; i < M - 1; ++i)
                for (usize j = 0; j < N - 1; ++j)
                    inv.unitVectors[j][i] = unitVectors[i][j] * invScaleSq[j];

            for (usize i = 0; i < N - 1; ++i) {
                for (usize j = 0; j < N - 1; ++j)
                    inv.unitVectors[M - 1][i] -= unitVectors[i][j] * unitVectors[N - 1][j];
                inv.unitVectors[M - 1][i] *= invScaleSq[i];
            }
            inv[M - 1][N - 1] = 1.0f;
            return inv;
        }
        float Trace() const requires SquareMatrix { // diagonal sum
            float result = 0;
            for (usize i = 0; i < N; ++i)
                result += unitVectors[i][i];
            return result;
        }

        Column TransformLinear(const Row& vector) const {
            Column result;
            for (usize i = 0; i < N; ++i) {
                for (usize j = 0; j < M; ++j) {
                    result[i] += vector[j] * unitVectors[j][i];
                }
            }
            return result;
        }
        ColumnAff Transform(const RowAff& vector) const {
            ColumnAff result;
            for (usize i = 0; i < N - 1; ++i) {
                for (usize j = 0; j < M - 1; ++j) {
                    result[i] += vector[j] * unitVectors[j][i];
                }
                result[i] += unitVectors[M - 1][i]; // translation is always applied
            }
            return result;
        }
        Super ScalarMul(float s) const {
            Super result { Uninit };
            for (usize i = 0; i < N * M; ++i) {
                result.GetElm(i) = GetElm(i) * s;
            }
            return result;
        }
        Super& ScalarMulAssign(float s) {
            float* m = &unitVectors[0][0];
            for (usize i = 0; i < N * M; ++i) m[i] *= s;
            return *this;
        }
        // NxM -> can transform M-d vectors -> MxP matrices
        template <usize P> Matrix<M, P> Mul(const Matrix<P, N>& other) const {
            Matrix<P, M> result { Uninit };
            for (usize i = 0; i < P; ++i) {
                for (usize j = 0; j < M; ++j) {
                    for (usize k = 0; k < N; ++k) {
                        result.unitVectors[i][j] += unitVectors[k][j] * other[i][k];
                    }
                }
            }
            return result;
        }
        Super Squared() const requires SquareMatrix {
            const float* m = &unitVectors[0][0];
            if constexpr (N == 2) {
                const float bc = m[1] * m[2], sAD = m[0] + m[3];
                return { m[0] * m[0] + bc, sAD  * m[1],
                         sAD  * m[2],      m[3] * m[3] + bc };
            } else if constexpr (N == 3) {
                const float bd  = m[1] * m[3], cg  = m[2] * m[6], fh  = m[5] * m[7];
                const float sAI = m[0] + m[8], sAE = m[0] + m[4], sEI = m[4] + m[8];
                return {
                    m[0] * m[0] + bd + cg, m[3] * sAE + m[5] * m[6], m[6] * sAI + m[3] * m[7],
                    m[1] * sAE + m[2] * m[7], m[4] * m[4] + bd + fh, m[5] * sEI + m[1] * m[6],
                    m[2] * sAI + m[1] * m[5], m[5] * sEI + m[2] * m[3], m[8] * m[8] + cg + fh
                };
            } else return Mul(*this);
        }

        const float& GetElm(usize i) const { return *(&unitVectors[0][0] + i); }
        float& GetElm(usize i) { return *(&unitVectors[0][0] + i); }
        const Column& GetCol(usize i) const { return unitVectors[i]; }
        Column& GetCol(usize i) { return unitVectors[i]; }
        const Column& operator[](usize i) const { return unitVectors[i]; }
        Column& operator[](usize i) { return unitVectors[i]; }
        Row GetRow(usize i) const {
            Row r;
            for (usize j = 0; j < M; ++j)
                r[j] = unitVectors[j][i];
            return r;
        }

        Super  operator* (float s) const { return ScalarMul(s); }
        Super& operator*=(float s) { return ScalarMulAssign(s); }

        Column    operator*(const Row& vector) const { return TransformLinear(vector); }
        ColumnAff operator*(const RowAff& vector) const { return Transform(vector); }

        template <usize P> Matrix<N, P> operator*(const Matrix<M, P>& m) const { return Mul(m); }
    };

    template <usize N, usize M> struct Matrix : IMatrix<N, M> {
        using IMatrix<N, M>::IMatrix;
    };

    template <> struct Matrix<2, 2> : IMatrix<2, 2> {
        using IMatrix::IMatrix;

        static Matrix RotationLin(const Rotor2D& rotation);
        Matrix& RotateByLin(const Rotor2D& rotation);
        Rotor2D GetRotationLin() const;
    };

    template <> struct Matrix<3, 3> : IMatrix<3, 3> {
        using IMatrix::IMatrix;

        static Matrix Rotation(const Rotor2D& rotation);
        Matrix& RotateBy(const Rotor2D& rotation);
        Rotor2D GetRotation() const;
        static Matrix RotationLin(const Rotor3D& rotation);
        Matrix& RotateByLin(const Rotor3D& rotation);
        Rotor3D GetRotationLin() const;

        Matrix<2> As2x2() const;
        MatrixTransform2D AsTransform() const;
        static Matrix Transform(const fv2& translate, const fv2& scale, const Rotor2D& rotate);
    };

    template <> struct Matrix<4, 4> : IMatrix<4, 4> {
        using IMatrix::IMatrix;
        Matrix Transpose() const;

        static Matrix Rotation(const Rotor3D& rotation);
        Matrix& RotateBy(const Rotor3D& rotation);
        Rotor3D GetRotation() const;

        Matrix<3> As3x3() const;
        MatrixTransform3D AsTransform() const;
        static Matrix OrthoProjection(const fRect3D& box);
        static Matrix PerspectiveProjection(const fRect3D& box);
        static Matrix PerspectiveFov(Radians fovDeg, float aspect, float near, float far);
        static Matrix Transform(const fv3& translate, const fv3& scale, const Rotor3D& rotate);
        static Matrix LookAt(const fv3& eye, const fv3& direction, const fv3& worldUp);
    };

    using Matrix2x2 = Matrix<2>;
    using Matrix2x3 = Matrix<2, 3>;
    using Matrix2x4 = Matrix<2, 4>;
    using Matrix3x2 = Matrix<3, 2>;
    using Matrix3x3 = Matrix<3>;
    using Matrix3x4 = Matrix<3, 4>;
    using Matrix4x2 = Matrix<4, 2>;
    using Matrix4x3 = Matrix<4, 3>;
    using Matrix4x4 = Matrix<4>;

    using Matrix2D = Matrix3x3;
    using Matrix3D = Matrix4x4;
}
