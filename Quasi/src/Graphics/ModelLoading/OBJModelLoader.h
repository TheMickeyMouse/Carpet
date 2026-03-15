#pragma once

#include "MTLMaterialLoader.h"
#include "OBJModel.h"

#include "Utils/Math/Vector.h"

namespace Quasi::Graphics {
    class OBJModelLoader {
    public:
        // https://en.wikipedia.org/wiki/Wavefront_.obj_file
        struct MaterialLib { String dir;  };
        struct UseMaterial { String name; };
        struct Object      { String name; };
        struct Group       { String name; }; // not impl

        struct Vertex       { Math::fv3 pos; };
        struct VertexTex    { Math::fv2 tex; };
        struct VertexNormal { Math::fv3 nrm; };
        struct VertexParam  { Math::fv3 prm; }; // not impl

        struct Face { int indices[3][3]; };
        struct Line { Vec<int> indices; }; // not impl

        struct SmoothShade { bool enabled; };

        struct OBJProperty : Variant<
            Empty,
            MaterialLib, UseMaterial, Object, Group,
            Vertex, VertexTex, VertexNormal, VertexParam,
            Face, Line,
            SmoothShade> {};
    private:
        Vec<OBJProperty> properties;
        MTLMaterialLoader mats;
        OBJModel model;

        Vec<Math::fv3> vertex;
        Vec<Math::fv2> vertexTexture;
        Vec<Math::fv3> vertexNormal;
        Vec<Face> faces;

        String folder, filename;
    public:
        OBJModelLoader() = default;

        void LoadFile(CStr filepath);
        void Load(Str string);
        void LoadMaterialFile(CStr filepath);
        void LoadMaterial(Str string);

        void ParseProperty(Str line);
        void ParseProperties(Str string);

        void CreateModel();
        void CreateObject(Span<const OBJProperty> objprop);
        void ResolveObjectIndices(OBJObject& obj);

        OBJModel& GetModel() { return model; }
        const OBJModel& GetModel() const { return model; }

        OBJModel&& RetrieveModel();

        // String DebugStr() const;
    };
}
