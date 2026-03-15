#pragma once

#include "Utils/Math/Vector.h"
#include "Utils/Math/Color.h"
#include "Utils/CStr.h"
#include "Utils/Text.h"
#include "Utils/Variant.h"

namespace Quasi::Graphics {
    struct MTLMaterial;
}

namespace Quasi::Graphics {
    class MTLMaterialLoader {
        public:
        struct NewMaterial { String name; };
        struct AmbientCol  { Math::fColor3 color; };
        struct DiffuseCol  { Math::fColor3 color; };
        struct SpecularCol { Math::fColor3 color; };
        struct EmissiveCol { Math::fColor3 color; };
        struct SpecularExp { float exp; };
        struct OpticalDen  { float density; };
        struct Dissolve    { float dissolve; };
        struct IlluminationType { u32 itype; };

        struct MTLProperty : Variant<Empty,
            NewMaterial,
            AmbientCol, DiffuseCol, SpecularCol, EmissiveCol,
            SpecularExp, OpticalDen, Dissolve,
            IlluminationType
        > {};
    private:
        Vec<MTLProperty> properties;
        Vec<MTLMaterial> materials; // TODO: use unordered_map for O(1)
    public:
        MTLMaterialLoader() = default;

        void LoadFile(CStr filename) { Load(Text::ReadFile(filename).Assert()); }
        void Load(Str string);

        void ParseProperty(Str line);
        void ParseProperties(Str string);

        // template <class MTL>
        // static MTLProperty CreateProperty(Str data);

        void CreateMaterial(Span<const MTLProperty> matprop);
        void CreateMaterials();

        // String DebugStr() const;

        friend class OBJModelLoader;
    };
}
