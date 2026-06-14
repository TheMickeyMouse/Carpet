#include "Geometry.h"

#include "Utils/Math/Transform3D.h"

namespace Quasi::Graphics {
    Geometry3D Geometry3D::WithCap(usize vCount, usize fCount) {
        return { Vec<Math::fv3>::WithCap(vCount), Vec<Math::fv3>::WithCap(vCount), Vec<Triplet>::WithCap(fCount) };
    }

    Geometry3D Geometry3D::FromVertices(Vec<Math::fv3> v, Vec<Triplet> i, bool smooth) {
        Geometry3D g { std::move(v), {}, std::move(i) };
        if (smooth) g.RecalcNormals(); else g.RecalcNormalsFlat();
        return g;
    }

    Geometry3D Geometry3D::FromVertAndNorm(Vec<Math::fv3> v, Vec<Math::fv3> n, Vec<Triplet> i) {
        return { std::move(v), std::move(n), std::move(i) };
    }

    void Geometry3D::RecalcNormals() {
        normals.Resize(vertices.Length());
        for (const auto [i, j, k] : indices) {
            const Math::fv3 n = (vertices[j] - vertices[i]).Cross(vertices[k] - vertices[i]);
            normals[i] += n;
            normals[j] += n;
            normals[k] += n;
        }
        // auto averages normals with larger faces being weighted more
        for (auto& n : normals) {
            n = n.Norm();
        }
    }

    void Geometry3D::RecalcNormalsFlat() {
        Vec<Math::fv3> points;
        normals.Clear();
        for (const auto [i, j, k] : indices) {
            const Math::fv3& A = vertices[i], &B = vertices[j], &C = vertices[k], n = (B - A).Cross(C - A);
            points.Push(A);
            points.Push(B);
            points.Push(C);
            normals.Push(n); normals.Push(n); normals.Push(n); // dup 3 for each point
        }
        vertices = std::move(points);
    }

    Geometry3D& Geometry3D::ApplyTransform(const Math::Transform3D& model) {
        for (auto& p : vertices) {
            p = model.Mul(p);
        }
        for (auto& n : normals) {
            n = model.MulN(n);
        }
        return *this;
    }

    void Geometry3D::Batch::PushV(const Math::fv3& v) {
        geometry.vertices.Push(v);
    }

    void Geometry3D::Batch::PushV(const Math::fv3& v, const Math::fv3& n) {
        geometry.vertices.Push(v);
        geometry.normals.Push(n);
    }

    void Geometry3D::Batch::PushVs(Span<const Math::fv3> vs, Span<const Math::fv3> ns) {
        geometry.vertices.Extend(vs);
        geometry.normals.Extend(ns);
    }

    void Geometry3D::Batch::PushFace(const Face3D& f) {
        PushVs(f.v, f.n); PushI(Triplet { 0, 1, 2 } + geometry.VOff());
    }
    
    void Geometry3D::Batch::Add(const Geometry3D& g) {
        PushIs(g.indices, geometry.VOff());
        PushVs(g.vertices, g.normals);
    }

    Geometry3D Geometry3D::Combine(Span<const Geometry3D> geoms) {
        usize vCount = 0, fCount = 0;
        for (const Geometry3D& g : geoms) { vCount += g.VOff(); fCount += g.FaceCount(); }
        Geometry3D sum = WithCap(vCount, fCount);
        for (const Geometry3D& g : geoms) { sum->Add(g); }
        return sum;
    }

    void Geometry3D::Deform(FuncRef<void(Face3D& f)> gpass) {
        for (const auto [i, j, k] : indices) {
            Face3D f = { { vertices[i], vertices[j], vertices[k] },
                       { normals[i],  normals[j],  normals[k]  } };
            gpass(f);
            vertices[i] = f.v[0], vertices[j] = f.v[1], vertices[k] = f.v[2];
            normals[i]  = f.n[0], normals[j]  = f.n[1], normals[k]  = f.n[2];
        }
    }

    Geometry3D Geometry3D::Pass(FuncRef<void(const Face3D& f, Batch b)> gpass) {
        Geometry3D g;
        for (const auto [i, j, k] : indices) {
            Face3D f = { { vertices[i], vertices[j], vertices[k] },
                       { normals[i],  normals[j],  normals[k]  } };
            gpass(f, g.NewBatch());
        }
        return g;
    }

    void Geometry3D::Clear() {
        vertices.Clear(); normals.Clear(); indices.Clear();
    }

    Geometry2D Geometry2D::WithCap(usize vCount, usize fCount) {
        return { Vec<Math::fv2>::WithCap(vCount), Vec<Triplet>::WithCap(fCount) };
    }

    Geometry2D Geometry2D::FromVertices(Vec<Math::fv2> v, Vec<Triplet> i) {
        return { std::move(v), std::move(i) };
    }

    Geometry2D& Geometry2D::ApplyTransform(const Math::Transform2D& model) {
        for (auto& p : vertices) {
            p = model.Mul(p);
        }
        return *this;
    }

    void Geometry2D::Batch::PushV(const Math::fv2& v) {
        geometry.vertices.Push(v);
    }

    void Geometry2D::Batch::PushVs(Span<const Math::fv2> vs) {
        geometry.vertices.Extend(vs);
    }

    void Geometry2D::Batch::Add(const Geometry2D& g) {
        PushIs(g.indices, geometry.VOff());
        PushVs(g.vertices);
    }

    Geometry2D Geometry2D::Combine(Span<const Geometry2D> geoms) {
        usize vCount = 0, fCount = 0;
        for (const Geometry2D& g : geoms) { vCount += g.VOff(); fCount += g.FaceCount(); }
        Geometry2D sum = WithCap(vCount, fCount);
        for (const Geometry2D& g : geoms) { sum->Add(g); }
        return sum;
    }

    void Geometry2D::Clear() {
        vertices.Clear(); indices.Clear();
    }
} // Quasi