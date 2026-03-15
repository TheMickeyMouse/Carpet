#pragma once
#include "Triplet.h"
#include "Utils/Vec.h"
#include "Utils/Math/Vector.h"
#include "GLs/VertexElement.h"

namespace Quasi::Math {
    struct Transform3D;
}

namespace Quasi::Graphics {
    template <IVertex Vtx> class Mesh;

    template <class Super>
    struct IBatch {
    protected:
        const Super& super() const { return static_cast<const Super&>(*this); }
        Super& super() { return static_cast<Super&>(*this); }
    public:
        u32 offset = 0;

        void PushI(Triplet i)                        { super().Indices().Push(i + offset); }
        void PushIs(Span<const Triplet> is)          { PushIs(is, offset); }
        void PushIs(Span<const Triplet> is, u32 off) {
            const usize tail = super().Indices().Length();
            super().Indices().Extend(is);
            for (auto& i : super().Indices().Skip(tail)) {
                i += off;
            }
        }

        void Tri(u32 i, u32 j, u32 k) {
            PushI({ i, j, k });
        }
        void Quad(u32 i, u32 j, u32 k, u32 l) {
            PushI({ i, j, l }); PushI({ j, k, l });
        }
        void TriStrip(Span<const u32> strip) {
            u32 tri[3] = { offset + strip[0], 0, offset + strip[1] };
            for (u32 i = 2; i < strip.Length(); ++i) {
                tri[1 ^ (i & 1)] = tri[2];
                tri[2] = offset + strip[i];
                super().Indices().Push({ tri[0], tri[1], tri[2] });
            }
        }
        void TriFan  (Span<const u32> fan) {
            const u32 center = offset + fan[0];
            u32 a = offset + fan[1];
            for (u32 i = 2; i < fan.Length(); ++i) {
                const u32 b = offset + fan[i];
                super().Indices().Push({ center, a, b });
                a = b;
            }
        }

        Super* operator->() { return &super(); }
    };

    struct Face3D {
        Math::fv3 v[3], n[3];
    };

    class Geometry3D {
    public:
        Vec<Math::fv3> vertices, normals;
        Vec<Triplet> indices;
    private:
        Geometry3D(Vec<Math::fv3> v, Vec<Math::fv3> n, Vec<Triplet> i) : vertices(std::move(v)), normals(std::move(n)), indices(std::move(i)) {}
    public:
        Geometry3D() = default;

        static Geometry3D WithCap(usize vCount, usize fCount);
        static Geometry3D FromVertices(Vec<Math::fv3> v, Vec<Triplet> i, bool smooth = true);
        static Geometry3D FromVertAndNorm(Vec<Math::fv3> v, Vec<Math::fv3> n, Vec<Triplet> i);

        void RecalcNormals();
        void RecalcNormalsFlat(); // this may be a little inefficient because faces need to be duplicated

        Geometry3D& ApplyTransform(const Math::Transform3D& model);

        u32 VOff() const { return vertices.Length(); }
        u32 FaceCount() const { return indices.Length(); }

        struct Batch : IBatch<Batch> {
            Geometry3D& geometry;

            Vec<Triplet>& Indices() { return geometry.indices; }
            void PushV(const Math::fv3& v);
            void PushV(const Math::fv3& v, const Math::fv3& n);
            void PushVs(Span<const Math::fv3> vs, Span<const Math::fv3> ns = {});

            void PushFace(const Face3D& f);
            // moving isnt that efficient bc vertices are easy to copy
            void Add(const Geometry3D& g);

            Batch NewBatch() { return { { geometry.VOff() }, geometry }; }
            void Reload() { offset = geometry.VOff(); }
        };
        Batch NewBatch()   { return { { VOff() }, *this }; }
        Batch operator->() { return { { 0 }, *this }; }

        static Geometry3D Combine(Span<const Geometry3D> geoms);

        void Deform(FuncRef<void(Face3D& f)> gpass);
        Geometry3D Pass(FuncRef<void(const Face3D& f, Batch b)> gpass);

        template <FnArgs<const Math::fv3&, const Math::fv3&> F, class T = FuncResult<F, const Math::fv3&, const Math::fv3&>>
        Mesh<T> IntoMesh(F&& map);

        void Clear();
    };

    class Geometry2D {
    public:
        Vec<Math::fv2> vertices;
        Vec<Triplet> indices;
    private:
        Geometry2D(Vec<Math::fv2> v, Vec<Triplet> i) : vertices(std::move(v)), indices(std::move(i)) {}
    public:
        Geometry2D() = default;

        static Geometry2D WithCap(usize vCount, usize fCount);
        static Geometry2D FromVertices(Vec<Math::fv2> v, Vec<Triplet> i);

        Geometry2D& ApplyTransform(const Math::Transform2D& model);

        u32 VOff() const { return vertices.Length(); }
        u32 FaceCount() const { return indices.Length(); }

        struct Batch : IBatch<Batch> {
            Geometry2D& geometry;

            Vec<Triplet>& Indices() { return geometry.indices; }
            void PushV(const Math::fv2& v);
            void PushVs(Span<const Math::fv2> vs);

            // moving isnt that efficient bc vertices are easy to copy
            void Add(const Geometry2D& g);

            Batch NewBatch() { return { { geometry.VOff() }, geometry }; }
            void Reload() { offset = geometry.VOff(); }
        };
        Batch NewBatch()   { return { { VOff() }, *this }; }
        Batch operator->() { return { { 0 }, *this }; }

        static Geometry2D Combine(Span<const Geometry2D> geoms);

        // void Deform(FuncRef<void(Face2D& f)> gpass);
        // Geometry2D Pass(FuncRef<void(const Face2D& f, Batch b)> gpass);

        template <FnArgs<const Math::fv2&> F, class T = FuncResult<F, const Math::fv2&>>
        Mesh<T> IntoMesh(F&& map);

        void Clear();
    };
} // Quasi