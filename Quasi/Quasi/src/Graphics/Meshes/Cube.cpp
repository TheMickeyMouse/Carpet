#include "MeshBuilder.h"

namespace Quasi::Graphics::Meshes {
    void Cube::MergeImpl(Geometry3D::Batch batch) const {
        using namespace Math;
        static constexpr u16 cornerData[6] {
            0b000'100'110'010,
            0b001'011'111'101,
            0b000'001'101'100,
            0b010'110'111'011,
            0b000'010'011'001,
            0b100'101'111'110,
        };
        for (usize i = 0; i < 6; ++i) {
            auto meshp = batch.NewBatch();
            meshp.Quad(0, 1, 2, 3);

            fv3 n;
            n[i / 2] = i % 2 ? 1 : -1;
            const u32 quad = cornerData[i];
            const bool corners[4][3] {
                { (quad >> 0 & 1) == 1, (quad >> 1  & 1) == 1, (quad >> 2  & 1) == 1 },
                { (quad >> 3 & 1) == 1, (quad >> 4  & 1) == 1, (quad >> 5  & 1) == 1 },
                { (quad >> 6 & 1) == 1, (quad >> 7  & 1) == 1, (quad >> 8  & 1) == 1 },
                { (quad >> 9 & 1) == 1, (quad >> 10 & 1) == 1, (quad >> 11 & 1) == 1 },
            };
            meshp.PushV(fv3::FromCorner(corners[0], hside), n);
            meshp.PushV(fv3::FromCorner(corners[1], hside), n);
            meshp.PushV(fv3::FromCorner(corners[2], hside), n);
            meshp.PushV(fv3::FromCorner(corners[3], hside), n);
        }
    }
}