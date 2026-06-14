#include "MeshBuilder.h"

namespace Quasi::Graphics::Meshes {
    void Arrow3D::MergeImpl(Geometry3D::Batch batch) const {
        static constexpr float DEFAULT_TIP_SIZE = 0.18f,
                               MAX_TIP_SIZE = 0.13f,
                               THICKNESS_FACTOR = 0.4f,
                               INV_NORMAL_LEN = 2 / (float)Math::ROOT_5;
        
        using namespace Math;
        const auto [fwd, len] = (end - start).NormAndLen();
        const float tipSize = std::max(len * MAX_TIP_SIZE, scale * DEFAULT_TIP_SIZE),
                    cylRadius = tipSize * THICKNESS_FACTOR;

        const fv3 beforeTip = end - fwd * (tipSize * 2);
        fv3 planeX = fwd.AnyTangent();

        const u32 divisions = 3 << subdivisions;
        {
            const Rotor2D halfRot = Radians(f32s::Comp(-(int)subdivisions, PI / 3.0f));
            const Matrix3x3 step = Quaternion { halfRot.Cos(), fwd * halfRot.Sin() }.AsMatrixLinear();
            fv3 p = planeX;
            const fv3 halfFwd = fwd * (0.5f * INV_NORMAL_LEN);
            const u32 divisionsTimes4 = divisions * 4;
            for (u32 i = 0; i < divisionsTimes4; i += 4) {
                const u32 w = i == 0 ? divisionsTimes4 : i;
                const fv3 r = step * p, pn = p * INV_NORMAL_LEN + halfFwd;
                batch.PushV(end,                     0);
                batch.PushV(beforeTip + p * tipSize, pn);
                batch.Tri(i, i + 1, w - 3);
                const fv3 q = p * cylRadius;
                batch.PushV(beforeTip + q, p);
                batch.PushV(start     + q, p);
                batch.Quad(i + 2, i + 3, w - 1, w - 2);
                p = r;
            }
        }

        Geometry3D::Batch tip = batch.NewBatch();
        planeX *= tipSize;
        const fv3 n = -fwd;
        Rotor3D step = Rotor3D::FromTrig(0.5f, HALF_ROOT_3, fwd);
        {
            const fv3 planeX120 = step.Rotate(planeX),
                      cylX120 = planeX120 * THICKNESS_FACTOR,
                      cylX = planeX * THICKNESS_FACTOR;
            tip.PushV(beforeTip + planeX120,            n);
            tip.PushV(start     + cylX120,              n);
            tip.PushV(beforeTip + planeX,               n);
            tip.PushV(start     + cylX,                 n);
            tip.PushV(beforeTip - (planeX + planeX120), n);
            tip.PushV(start     - (cylX + cylX120),     n);

            tip.Tri(2, 0, 4);
            tip.Tri(3, 1, 5);
        }

        for (u32 i = 0; i < subdivisions; ++i) {
            const Rotor3D half = step.Halved();
            fv3 vertex = half * planeX;

            u32 p = 2, q = (6 << i) + 1;
            for (u32 j = 0; j < (3 << i); ++j) {
                tip.PushV(beforeTip + vertex, n);
                tip.PushV(start     + vertex * THICKNESS_FACTOR, n);
                vertex = step * vertex;

                const u32 r = q >> u32s::CountRightOnes(q);
                tip.Tri(p,     q - 1, r);
                tip.Tri(p + 1, q,     r + 1);
                p = r;
                q += 2;
            }
            step = half;
        }
    }
}
