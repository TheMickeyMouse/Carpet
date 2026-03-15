#pragma once
#include "Geometry.h"
#include "RenderObject.h"
#include "Triplet.h"

namespace Quasi::Graphics {
    template <IVertex Vtx>
    class Mesh {
    public:
        Vec<Vtx> vertices;
        Vec<Triplet> indices;
    public:
        Mesh() = default;
        Mesh(IList<Vtx> v, IList<Triplet> i) : vertices(Vecs::FromIList(v)), indices(Vecs::FromIList(i)) {}
        Mesh(Vec<Vtx> v, Vec<Triplet> i)
            : vertices(std::move(v)), indices(std::move(i)) {}

        static Mesh WithCap(usize vCount, usize fCount) {
            return { Vec<Vtx>::WithCap(vCount), Vec<Triplet>::WithCap(fCount) };
        }

        void ApplyTransform(const Vtx::Transformation& model) {
            for (auto& v : vertices) {
                v = v.Mul(model);
            }
        }

        u32 VOff() const { return vertices.Length(); }
        u32 FaceCount() const { return indices.Length(); }

        template <FnArgs<const Vtx&> F, class T = FuncResult<F, const Vtx&>>
        Mesh<T> GeometryConvert(F&& geometryPass) {
            Mesh<T> converted;
            converted.indices = indices;
            converted.vertices.Reserve(vertices.Length());

            for (const Vtx& v : vertices)
                converted.vertices.Push(geometryPass(v));
            return converted;
        }

        struct Batch : IBatch<Batch> {
            Mesh& mesh;

            Vec<Triplet>& Indices() { return mesh.indices; }
            void PushV(const Vtx& v)            { mesh.vertices.Push(v); }
            void PushVs(Span<const Vtx> vs)     { mesh.vertices.Extend(vs); }

            // moving isnt that efficient bc vertices are easy to copy
            void Add(const Mesh& m) {
                this->PushIs(m.indices, mesh.VOff());
                PushVs(m.vertices);
            }

            Batch NewBatch() { return { { mesh.VOff() }, mesh }; }
            void Reload() { this->offset = mesh.VOff(); }
        };
        Batch NewBatch()   { return { { VOff() }, *this }; }
        Batch operator->() { return { { 0 }, *this }; }

        static Mesh Combine(Span<const Mesh> meshes) {
            usize vCount = 0, fCount = 0;
            for (const Mesh& m : meshes) { vCount += m.VOff(); fCount += m.FaceCount(); }
            Mesh sum = WithCap(vCount, fCount);
            Batch b = sum.NewBatch();
            for (const Mesh& m : meshes) { b.Add(m); }
            return sum;
        }

        void Clear() {
            vertices.Clear();
            indices.Clear();
        }
    };

    template <FnArgs<const Math::fv3&, const Math::fv3&> F, class T>
    Mesh<T> Geometry3D::IntoMesh(F&& map) {
        Mesh<T> mesh;
        mesh.indices = std::move(indices);
        mesh.vertices.Reserve(vertices.Length());
        for (usize i = 0; i < vertices.Length(); ++i) {
            mesh.vertices.Push(map(vertices[i], normals[i]));
        }
        return mesh;
    }

    template <FnArgs<const Math::fv2&> F, class T>
    Mesh<T> Geometry2D::IntoMesh(F&& map) {
        Mesh<T> mesh;
        mesh.indices = std::move(indices);
        mesh.vertices.Reserve(vertices.Length());
        for (usize i = 0; i < vertices.Length(); ++i) {
            mesh.vertices.Push(map(vertices[i]));
        }
        return mesh;
    }
}
