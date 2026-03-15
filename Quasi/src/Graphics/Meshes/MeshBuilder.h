#pragma once

#include "Geometry.h"

namespace Quasi::Graphics::Meshes {
    template <class Super>
    struct IMeshBuilder2D {
        const Super& super() const { return static_cast<const Super&>(*this); }
        Super& super() { return static_cast<Super&>(*this); }

        void Merge(Geometry2D::Batch out) {
            return super().MergeImpl(out);
        }
        Geometry2D Create() {
            Geometry2D geom;
            Merge(geom.NewBatch());
            return geom;
        }
    };

    template <class Super>
    struct IMeshBuilder3D {
        const Super& super() const { return static_cast<const Super&>(*this); }
        Super& super() { return static_cast<Super&>(*this); }

        void Merge(Geometry3D::Batch out) {
            return super().MergeImpl(out);
        }
        Geometry3D Create() {
            Geometry3D geom;
            Merge(geom.NewBatch());
            return geom;
        }
    };

#define MESHB(NAME, DIM, ...) \
    struct NAME : IMeshBuilder##DIM<NAME> { \
        __VA_ARGS__ \
        void MergeImpl(Geometry##DIM::Batch batch) const; \
    };

    MESHB(Circle, 2D,
        float radius = 1.0f;
        u32 subdivisions = 4;
        Circle(float r = 1.0f, u32 sub = 4) : radius(r), subdivisions(sub) {}
    )
    MESHB(Quad, 2D,
        float hside = 1.0f;
        Quad(float halfSide = 1.0) : hside(halfSide) {}
    )
    MESHB(Stadium, 2D,
        Math::fv2 start, end = { 0, 1 };
        float radius = 1.0f;
        u32 subdivisions = 4;
        Stadium(const Math::fv2& start = {}, const Math::fv2& end = { 0, 1 }, float r = 1.0f, u32 sub = 4)
            : start(start), end(end), radius(r), subdivisions(sub) {}
    )
    MESHB(Arrow2D, 2D,
        Math::fv2 start, end;
        float scale = 1.0f;
        Arrow2D(const Math::fv2& start, const Math::fv2& end, float scale = 1.0f)
            : start(start), end(end), scale(scale) {}
    )

    MESHB(Cube, 3D,
        float hside = 1.0f;
        Cube(float halfSide = 1.0) : hside(halfSide) {}
    )
    MESHB(Plane, 3D,
        float hside = 1.0f;
        Plane(float halfSide = 1.0) : hside(halfSide) {}
    )
    MESHB(Icosphere, 3D,
        float radius = 1.0f;
        u32 divisions = 0;
        Icosphere(float r = 1, u32 subdivisions = 3) : radius(r), divisions(1 << subdivisions) {}
    )
    MESHB(Sphere, 3D,
        float radius = 1.0f;
        Math::uv2 sections;
        Sphere(float r = 1, u32 lon = 32, u32 lat = 32) : radius(r), sections(lon, lat) {}
    )
    MESHB(Capsule, 3D,
        Math::fv3 start = 0, end = { 0, 1, 0 };
        float radius = 1;
        Math::uv2 sections = { 32, 16 };
        Capsule(const Math::fv3& start = 0, const Math::fv3& end = { 0, 1, 0 }, float r = 1, u32 lon = 32, u32 lat = 16)
            : start(start), end(end), radius(r), sections(lon, lat) {}
    )
    MESHB(Arrow3D, 3D,
        Math::fv3 start, end;
        float scale = 1.0f;
        u32 subdivisions = 3;
        Arrow3D(const Math::fv3& start, const Math::fv3& end, float scale = 1, u32 sub = 3)
            : start(start), end(end), scale(scale), subdivisions(sub) {}
    )
#undef MESHB
}
