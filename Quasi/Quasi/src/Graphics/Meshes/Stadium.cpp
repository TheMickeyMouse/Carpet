#include "MeshBuilder.h"

namespace Quasi::Graphics::Meshes {
    void Stadium::MergeImpl(Geometry2D::Batch batch) const {
        using namespace Math;

        const fv2 Y = (end - start).Norm(radius);
        const fv2 X = Y.PerpendRight();

        {
            batch.PushV(end + X);
            batch.PushV(end - X);
            batch.PushV(end + Y);
            batch.Tri(0, 2, 1);

            Rotor2D step = Rotor2D::FromComplex({ 0, 1 });
            for (u32 i = 0; i < subdivisions; ++i) {
                const Rotor2D half = step.Halved();
                fv2 vertex = half.Rotate(X);
                u32 p = 0, q = (2 << i) + 1;
                for (u32 j = 0; j < (2 << i); ++j) {
                    batch.PushV(end + vertex);
                    vertex = vertex.RotateBy(step);
                    const u32 r = (q >> (u32s::CountRightZeros(q) + 1)) + 1;
                    batch.Tri(p, q, r);
                    p = r;
                    ++q;
                }
                step = half;
            }
        }
        {
            auto m = batch.NewBatch();
            m.PushV(start - X);
            m.PushV(start + X);
            m.PushV(start - Y);
            m.Tri(0, 2, 1);

            Rotor2D step = Rotor2D::FromComplex({ 0, 1 });
            for (u32 i = 0; i < subdivisions; ++i) {
                const Rotor2D half = step.Halved();
                fv2 vertex = half.Rotate(X);
                u32 p = 0, q = (2 << i) + 1;
                for (u32 j = 0; j < (2 << i); ++j) {
                    m.PushV(start - vertex);
                    vertex = vertex.RotateBy(step);
                    const u32 r = (q >> (u32s::CountRightZeros(q) + 1)) + 1;
                    m.Tri(p, q, r);
                    p = r;
                    ++q;
                }
                step = half;
            }
        }
        const u32 secondHalf = (2 << subdivisions) + 1;
        batch.Quad(1, secondHalf, secondHalf + 1, 0);
    }
}
