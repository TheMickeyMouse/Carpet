#pragma once
#include "Mesh.h"
#include "GLs/VertexElement.h"

namespace Quasi::Graphics {
    using OBJVertex = VertexTextureNormal3D;

    struct MTLMaterial { // https://en.wikipedia.org/wiki/Wavefront_.obj_file
        String name;
        // ambient, diffuse, specular, emissive color
        Math::fColor3 Ka, Kd, Ks, Ke;
        // specular exponent, optical density
        float Ns, Ni;
        // dissolve
        float d;
        // illumination
        int illum;
    };

    struct OBJModel;
    struct OBJObject {
        String name;
        Mesh<OBJVertex> mesh;
        bool smoothShading;
        int materialIndex = -1;
        OBJModel* model;
    };

    struct OBJModel {
        Vec<OBJObject> objects;
        Vec<MTLMaterial> materials;

        Vec<Mesh<OBJVertex>> RetrieveMeshes();
    };
}
