#include "OBJModel.h"

namespace Quasi::Graphics {
    Vec<Mesh<OBJVertex>> OBJModel::RetrieveMeshes() {
        Vec<Mesh<OBJVertex>> meshes = Vec<Mesh<OBJVertex>>::WithCap(objects.Length());
        for (OBJObject& obj : objects) {
            meshes.Push(std::move(obj.mesh));
        }
        return meshes;
    }
}
