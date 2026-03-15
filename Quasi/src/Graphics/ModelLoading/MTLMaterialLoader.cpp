#include "MTLMaterialLoader.h"
#include <ranges>

#include "OBJModel.h"
#include "Utils/Match.h"
#include "Utils/Iter/LinesIter.h"
#include "Utils/Text/Parsing.h"

namespace Quasi::Graphics {
    void MTLMaterialLoader::Load(Str string) {
        ParseProperties(string);
        CreateMaterials();
    }

    void MTLMaterialLoader::ParseProperty(Str line) {
        const auto [prefix, data] = line.SplitOnce(' ');

        MTLProperty prop = { Empty {} };
        Qmatch$ (prefix, (
            case ("newmtl") prop.Set(NewMaterial { String(data) });,
            case ("Ka")     prop.Set(AmbientCol  { { Math::fv3::Parse(data, " ").UnwrapOr(Math::fv3 {}) } });,
            case ("Kd")     prop.Set(DiffuseCol  { { Math::fv3::Parse(data, " ").UnwrapOr(Math::fv3 {}) } });,
            case ("Ks")     prop.Set(SpecularCol { { Math::fv3::Parse(data, " ").UnwrapOr(Math::fv3 {}) } });,
            case ("Ke")     prop.Set(EmissiveCol { { Math::fv3::Parse(data, " ").UnwrapOr(Math::fv3 {}) } });,
            case ("Ns")     prop.Set(SpecularExp { Text::Parse<float>(data).UnwrapOr(f32s::NAN) });,
            case ("Ni")     prop.Set(OpticalDen  { Text::Parse<float>(data).UnwrapOr(f32s::NAN) });,
            case ("d")      prop.Set(Dissolve    { Text::Parse<float>(data).UnwrapOr(f32s::NAN) });,
            case ("illum")  prop.Set(IlluminationType { Text::Parse<u32>(data).UnwrapOr(-1) });
        ))
        if (!prop.Is<Empty>())
            properties.Push(std::move(prop));
    }

    void MTLMaterialLoader::ParseProperties(Str string) {
        using namespace std::literals;
        for (const Str line : string.Lines()) {
            ParseProperty(line);
        }
    }

    void MTLMaterialLoader::CreateMaterial(Span<const MTLProperty> matprop) {
        if (matprop.IsEmpty() || !matprop[0].Is<NewMaterial>()) return;

        materials.Push({});
        MTLMaterial& mat = materials.Last();
        mat.name = matprop[0].As<NewMaterial>()->name;

        for (const MTLProperty& prop : matprop.Skip(1)) {
            prop.Visit(
                [&] (const AmbientCol&       x) { mat.Ka    = x.color;    },
                [&] (const DiffuseCol&       x) { mat.Kd    = x.color;    },
                [&] (const SpecularCol&      x) { mat.Ks    = x.color;    },
                [&] (const EmissiveCol&      x) { mat.Ke    = x.color;    },
                [&] (const SpecularExp&      x) { mat.Ns    = x.exp;      },
                [&] (const OpticalDen&       x) { mat.Ni    = x.density;  },
                [&] (const Dissolve&         x) { mat.d     = x.dissolve; },
                [&] (const IlluminationType& x) { mat.illum = x.itype;    },
                [] (const auto&) {}
            );
        }
    }

    void MTLMaterialLoader::CreateMaterials() {
        u32 lastMat = 0;
        for (u32 i = 1; i < properties.Length(); ++i) {
            if (!properties[i].Is<NewMaterial>()) continue;
            Span<const MTLProperty> mat = properties.Subspan(lastMat, i - 1 - lastMat);
            lastMat = i;
            CreateMaterial(mat);
        }
        CreateMaterial(properties.AsSpan().Skip(lastMat));
    }

    // String MTLMaterialLoader::DebugStr() const {
    //     String ss {};
    //     for (const MTLProperty& p : properties) {
    //         p.Visit(
    //             [&] (const NewMaterial&      x) { ss += "newmtl: ";       ss += x.name;                     },
    //             [&] (const AmbientCol&       x) { ss += "ambient: ";      ss += x.color.hexcode();          },
    //             [&] (const DiffuseCol&       x) { ss += "diffuse: ";      ss += x.color.hexcode();          },
    //             [&] (const SpecularCol&      x) { ss += "specular: ";     ss += x.color.hexcode();          },
    //             [&] (const EmissiveCol&      x) { ss += "emmisive: ";     ss += x.color.hexcode();          },
    //             [&] (const SpecularExp&      x) { ss += "specular exp: "; ss += Text::Format("{}", x.exp);      },
    //             [&] (const OpticalDen&       x) { ss += "optical den: ";  ss += Text::Format("{}", x.density);  },
    //             [&] (const Dissolve&         x) { ss += "dissolve: ";     ss += Text::Format("{}", x.dissolve); },
    //             [&] (const IlluminationType& x) { ss += "illumtype: ";    ss += Text::Format("{}", x.itype);    },
    //             [] (const auto&) {}
    //         );
    //     }
    //     return ss;
    // }
}
