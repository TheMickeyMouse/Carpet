#include "MeshBuilder.h"

namespace Quasi::Graphics::Meshes {
    void Circle::MergeImpl(Geometry2D::Batch batch) const {
#pragma region Data
        static constexpr float PRECOMPUTED_POINTS[] = {
            -0.5f,  Math::HALF_ROOT_3,
            +1,     0,                 // sub 0
            -0.5f, -Math::HALF_ROOT_3,

            +0.5f,  Math::HALF_ROOT_3, // sub 1
            -1,     0,
            +0.5f, -Math::HALF_ROOT_3,

            +Math::HALF_ROOT_3, +0.5f, // sub 2
            0, 1,
            -Math::HALF_ROOT_3, +0.5f,
            -Math::HALF_ROOT_3, -0.5f,
            0, -1,
            +Math::HALF_ROOT_3, -0.5f,

            +0.965925826289f,   +0.258819045103f, // sub 3
            +Math::HALF_ROOT_2, +Math::HALF_ROOT_2,
            +0.258819045103f,   +0.965925826289f,
            -0.258819045103f,   +0.965925826289f,
            -Math::HALF_ROOT_2, +Math::HALF_ROOT_2,
            -0.965925826289f,   +0.258819045103f,
            -0.965925826289f,   -0.258819045103f,
            -Math::HALF_ROOT_2, -Math::HALF_ROOT_2,
            -0.258819045103f,   -0.965925826289f,
            +0.258819045103f,   -0.965925826289f,
            +Math::HALF_ROOT_2, -Math::HALF_ROOT_2,
            +0.965925826289f,   -0.258819045103f,

            +0.991444861374f, +0.130526192220f, // sub 4
            +0.923879532511f, +0.382683432365f,
            +0.793353340291f, +0.608761429009f,
            +0.608761429009f, +0.793353340291f,
            +0.382683432365f, +0.923879532511f,
            +0.130526192220f, +0.991444861374f,
            -0.130526192220f, +0.991444861374f,
            -0.382683432365f, +0.923879532511f,
            -0.608761429009f, +0.793353340291f,
            -0.793353340291f, +0.608761429009f,
            -0.923879532511f, +0.382683432365f,
            -0.991444861374f, +0.130526192220f,
            -0.991444861374f, -0.130526192220f,
            -0.923879532511f, -0.382683432365f,
            -0.793353340291f, -0.608761429009f,
            -0.608761429009f, -0.793353340291f,
            -0.382683432365f, -0.923879532511f,
            -0.130526192220f, -0.991444861374f,
            +0.130526192220f, -0.991444861374f,
            +0.382683432365f, -0.923879532511f,
            +0.608761429009f, -0.793353340291f,
            +0.793353340291f, -0.608761429009f,
            +0.923879532511f, -0.382683432365f,
            +0.991444861374f, -0.130526192220f,
        };

        static constexpr u32 PRECOMPUTED_INDICES[] = {
            1, 0, 2,
            1, 3, 0, 0, 4, 2, 2, 5, 1,
            1, 6, 3, 3, 7, 0, 0, 8, 4, 4, 9, 2, 2, 10, 5, 5, 11, 1,
            1, 12, 6, 6, 13, 3, 3, 14, 7, 7, 15, 0, 0, 16, 8, 8, 17, 4, 4, 18, 9, 9, 19, 2, 2, 20, 10, 10, 21, 5, 5, 22, 11, 11, 23, 1,

            1, 24, 12, 12, 25, 6, 6, 26, 13, 13, 27, 3, 3, 28, 14, 14, 29, 7, 7, 30, 15, 15, 31, 0, 0, 32, 16, 16, 33, 8,
            8, 34, 17, 17, 35, 4, 4, 36, 18, 18, 37, 9, 9, 38, 19, 19, 39, 2, 2, 40, 20, 20, 41, 10, 10, 42, 21, 21, 43, 5,
            5, 44, 22, 22, 45, 11, 11, 46, 23, 23, 47, 1,
        };
#pragma endregion
        const u32 total = 3 << subdivisions;

        const u32 precompCount = std::min(total, 3u << 4);
        for (u32 i = 0; i < precompCount; ++i) {
            batch.PushV({ radius * PRECOMPUTED_POINTS[2 * i], radius * PRECOMPUTED_POINTS[2 * i + 1] });
        }
        for (u32 i = 0; i < (precompCount - 2); ++i) {
            const u32* ind = &PRECOMPUTED_INDICES[3 * i];
            batch.Tri(ind[0], ind[1], ind[2]);
        }

        if (subdivisions <= 4) return;

        Math::Rotor2D step = Math::Rotor2D::FromComplex({ 0.991444861374f, 0.130526192220f });
        for (u32 i = 4; i < subdivisions; ++i) {
            const Math::Rotor2D half = step.Halved();
            Math::fv2 vertex = half.IHat() * radius;

            // algorithm from https://oeis.org/search?q=12%2c6%2c13%2c3%2c14%2c7%20id:25480 binary perspective
            u32 p = 1, q = 3 << i;
            for (u32 j = 0; j < (3 << i); ++j) {
                batch.PushV(vertex);
                vertex = vertex.RotateBy(step);

                const u32 r = q >> (u32s::CountRightOnes(q) + 1);
                batch.Tri(p, q, r);
                p = r;
                ++q;
            }
            step = half;
        }
    }
}
