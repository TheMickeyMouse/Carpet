#include "MeshBuilder.h"

namespace Quasi::Graphics::Meshes {
    void Quad::MergeImpl(Geometry2D::Batch batch) const {
        batch.PushV({ +hside, +hside });
        batch.PushV({ -hside, +hside });
        batch.PushV({ -hside, -hside });
        batch.PushV({ +hside, -hside });
        batch.Quad(0, 1, 2, 3);
    }
} // Graphics::MeshUtils
