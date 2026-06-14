#include "MeshBuilder.h"

namespace Quasi::Graphics::Meshes {
    void Plane::MergeImpl(Geometry3D::Batch batch) const {
        batch.PushV({ +hside, 0, +hside }, { 0, 1, 0 });
        batch.PushV({ -hside, 0, +hside }, { 0, 1, 0 });
        batch.PushV({ -hside, 0, -hside }, { 0, 1, 0 });
        batch.PushV({ +hside, 0, -hside }, { 0, 1, 0 });
        batch.Quad(0, 1, 2, 3);
    }
} // Graphics::MeshUtils
