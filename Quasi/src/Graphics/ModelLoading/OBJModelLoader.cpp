#include "OBJModelLoader.h"
#include "Utils/Algorithm.h"
#include "Utils/Comparison.h"

#include "Utils/Iter/LinesIter.h"
#include "Utils/Text/Parsing.h"
#include "Utils/Iter/SplitIter.h"

namespace Quasi::Graphics {
    void OBJModelLoader::LoadFile(CStr filepath) {
        Text::SplitDirectory(filepath).TieTo(folder, filename);
        Load(Text::ReadFile(filepath).Assert());
    }

    void OBJModelLoader::Load(Str string) {
        ParseProperties(string);
        CreateModel();
    }

    void OBJModelLoader::LoadMaterialFile(CStr filepath) {
        const usize len = folder.Length() + filepath.Length() + 2;
        char* fullpath = Memory::QAlloca$(char, len),
            * acc = fullpath;

        Memory::MemCopy(acc, folder.Data(), folder.Length()); acc += folder.Length();
        *acc++ = '\\';
        Memory::MemCopy(acc, filepath.Data(), filepath.Length());


        mats.LoadFile(CStr::SliceUnchecked(fullpath, len));
        model.materials = std::move(mats.materials);
    }

    void OBJModelLoader::LoadMaterial(Str string) {
        mats.Load(string);
        model.materials = std::move(mats.materials);
    }

    void OBJModelLoader::ParseProperty(const Str line) {
        const OptionUsize spaceIdx = line.Find(' ');
        if (!spaceIdx) return;
        const auto [prefix, data] = line.SplitAt(*spaceIdx);

        OBJProperty prop = { Empty {} };

        switch (Memory::ReadZeroExtU64Big(prefix.Data(), prefix.Length())) {
            case "v"_u64:  prop.Set(Vertex       { Math::fv3::Parse(data, " ").UnwrapOr(Math::fv3 { f32s::NAN }) }); break;
            case "vt"_u64: prop.Set(VertexTex    { Math::fv2::Parse(data, " ").UnwrapOr(Math::fv2 { f32s::NAN }) }); break;
            case "vn"_u64: prop.Set(VertexNormal { Math::fv3::Parse(data, " ").UnwrapOr(Math::fv3 { f32s::NAN }) }); break;
            case "vp"_u64: prop.Set(VertexParam  { Math::fv3::Parse(data, " ").UnwrapOr(Math::fv3 { f32s::NAN }) }); break;
            case "f"_u64: {
                Face face;
                u32 i = 0;
                for (const Str idx : data.Split(" ")) {
                    if (i >= 3) break;
                    const auto [v, t, n] = Math::iv3::Parse(idx, "/",
                        [](Str x) -> Option<int> { return Text::Parse<int>(x).UnwrapOr(-1); }).UnwrapOr({ -1 });
                    face.indices[i][0] = v; face.indices[i][1] = t; face.indices[i][2] = n;
                    ++i;
                }
                if (i == 3) prop.Set(face);
            } break;
            case "l"_u64: {
                Vec<int> indices;
                for (const Str idx : data.Split(" ")) {
                    indices.Push(Text::Parse<int>(idx).UnwrapOr(-1));
                }
                prop.Set<Line>({ indices });
            } break;
            case "o"_u64:      prop.Set(Object { data }); break;
            case "g"_u64:      prop.Set(Group  { data }); break;
            case "s"_u64:      prop.Set(SmoothShade { data != "0" }); break;
            case "usemtl"_u64: prop.Set(UseMaterial { data }); break;
            case "mtllib"_u64: {
                String mtllibdir = data;
                mtllibdir.AddNullTerm();
                prop.Set(MaterialLib { std::move(mtllibdir) });
            } break;
            default:;
        }

        if (!prop.Is<Empty>())
            properties.Push(std::move(prop));
    }

    void OBJModelLoader::ParseProperties(Str string) {
        for (const Str line : string.Lines()) {
            ParseProperty(line);
        }
    }

    void OBJModelLoader::CreateModel() {
        u32 lastObj = 0;
        for (u32 i = 0; i < properties.Length(); ++i) {
            if (const auto matfile = properties[i].As<MaterialLib>()) {
                LoadMaterialFile(CStr::FromUnchecked(matfile->dir));
                ++lastObj;
                continue;
            }
            if (!properties[i].Is<Object>()) continue;

            const auto objprop = properties.Subspan(lastObj, i - lastObj);
            lastObj = i;
            CreateObject(objprop);
        }
        CreateObject(properties.Skip(lastObj));
    }

    void OBJModelLoader::CreateObject(Span<const OBJProperty> objprop) {
        if (objprop.IsEmpty() || !objprop[0].Is<Object>()) return;

        OBJObject& object = model.objects.Push({});
        object.model = &model;
        object.name = objprop[0].As<Object>()->name;

        for (const OBJProperty& prop : objprop.Skip(1)) {
            prop.Visit(
                [&] (const UseMaterial& usemat) {
                    const OptionUsize i = model.materials.FindIf(
                        [&](const MTLMaterial& m) { return m.name == usemat.name; }
                    );
                    if (!i) return;
                    object.materialIndex = (int)*i;
                },
                [&] (const Vertex&       v) { vertex       .Push(v.pos); },
                [&] (const VertexTex&    t) { vertexTexture.Push(t.tex); },
                [&] (const VertexNormal& n) { vertexNormal .Push(n.nrm); },
                [&] (const Face&         f) { faces.Push(f); },
                [&] (SmoothShade        ss) { object.smoothShading = ss.enabled; },
                [] (const auto&) {}
            );
        }
        ResolveObjectIndices(object);
    }

    void OBJModelLoader::ResolveObjectIndices(OBJObject& obj) {
        struct Cmp3 {
            Comparison operator()(const Math::iv3& tripleA, const Math::iv3& tripleB) const {
                const auto [ax, ay, az] = tripleA;
                const auto [bx, by, bz] = tripleB;
                return ax != bx ? Cmp::Between(ax, bx) : ay != by ? Cmp::Between(ay, by) : Cmp::Between(az, bz);
            }
        };

        // a hashset is actually worse than a vector lol, cuz i need indices
        Vec<Math::iv3> indices;
        for (const Face& f : faces) {
            indices.Push({ f.indices[0][0], f.indices[0][1], f.indices[0][2] });
            indices.Push({ f.indices[1][0], f.indices[1][1], f.indices[1][2] });
            indices.Push({ f.indices[2][0], f.indices[2][1], f.indices[2][2] });
        }
        indices.Sort(Cmp3 {});
        indices.RemoveDups();
        obj.mesh.vertices = indices.MapEach(
            [&] (const Math::iv3& triple) {
                return OBJVertex {
                    triple.x == -1 ? Math::fv3 {} : vertex[triple.x - 1],
                    triple.y == -1 ? Math::fv2 {} : vertexTexture[triple.y - 1],
                    triple.z == -1 ? Math::fv3 {} : vertexNormal[triple.z - 1]
                };
            }
        );

        Vec<Triplet>& ind = obj.mesh.indices;
        ind.Reserve(faces.Length());
        for (const Face& f : faces) {
            Math::iv3 v1 { f.indices[0][0], f.indices[0][1], f.indices[0][2] };
            Math::iv3 v2 { f.indices[1][0], f.indices[1][1], f.indices[1][2] };
            Math::iv3 v3 { f.indices[2][0], f.indices[2][1], f.indices[2][2] };
            const auto [_1, i1] = indices.AsSpan().BinarySearchWith([&] (const Math::iv3& x) { return Cmp3 {}(x, v1); });
            const auto [_2, i2] = indices.AsSpan().BinarySearchWith([&] (const Math::iv3& x) { return Cmp3 {}(x, v2); });
            const auto [_3, i3] = indices.AsSpan().BinarySearchWith([&] (const Math::iv3& x) { return Cmp3 {}(x, v3); });
            ind.Push({ (u32)i1, (u32)i2, (u32)i3 });
        }

        faces.Clear();
    }

    OBJModel&& OBJModelLoader::RetrieveModel() {
        return std::move(model);
    }

    // String OBJModelLoader::DebugStr() const {
    //     String ss {};
    //     for (const OBJProperty& p : properties) {
    //         p.Visit(
    //             [&] (const Vertex&       x) { ss += "v: ";      ss += Text::Format(x.pos); },
    //             [&] (const VertexTex&    x) { ss += "vt: ";     ss += Text::Format(x.tex); },
    //             [&] (const VertexNormal& x) { ss += "vn: ";     ss += Text::Format(x.nrm); },
    //             [&] (const VertexParam&  x) { ss += "vp: ";     ss += Text::Format(x.prm); },
    //             [&] (const Face&         x) { ss += "f: ";      ss += Text::ArrStr(x.indices, ", ", [] (const int (&vtn)[3]) { return Text::ArrStr(vtn, "/"); }); },
    //             [&] (const Line&         x) { ss += "l: ";      ss += Text::ArrStr(x.indices); },
    //             [&] (const Object&       x) { ss += "o: ";      ss += x.name; },
    //             [&] (const Group&        x) { ss += "g: ";      ss += x.name; },
    //             [&] (const SmoothShade&  x) { ss += "s: ";      ss += x.enabled ? "true" : "false"; },
    //             [&] (const UseMaterial&  x) { ss += "usemtl: "; ss += x.name; },
    //             [&] (const MaterialLib&  x) { ss += "mtllib: "; ss += x.dir;  },
    //             [] (const auto&) {}
    //         );
    //     }
    //     ss += "========\n";
    //     ss += mats.DebugStr();
    //     return ss;
    // }
}
