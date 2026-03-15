#include "MeshBuilder.h"

namespace Quasi::Graphics::Meshes {
    static constexpr float DEFAULT_TIP_SIZE = 0.35f, MAX_TIP_SIZE = 0.25f, THICKNESS_FACTOR = 0.1f;

    void Arrow2D::MergeImpl(Geometry2D::Batch batch) const {
        const auto [fwd, len] = (end - start).NormAndLen();
        const float tipSize   = std::min(len * MAX_TIP_SIZE, scale * DEFAULT_TIP_SIZE);
        /*   ^
         *  / \
         * /   \
         *  | |
         *  | |
         */
        // tip bit
        const Math::fv2 tipF = tipSize * fwd;
        batch.PushV(end);
        batch.PushV(end + tipF.ComplexMul({ -1, +0.5f }));
        batch.PushV(end + tipF.ComplexMul({ -1, -0.5f }));
        batch.Tri(0, 1, 2);

        const Math::fv2 thick = tipF.PerpendLeft() * THICKNESS_FACTOR, beforeTip = end - tipF;
        // length
        batch.PushV(start + thick);
        batch.PushV(start - thick);
        batch.PushV(beforeTip - thick);
        batch.PushV(beforeTip + thick);
        batch.Quad(3, 4, 5, 6);
    }
}
