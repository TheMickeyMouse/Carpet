#pragma once
#include "IShape2D.h"
#include "Utils/Vec.h"

namespace Quasi::Physics2D {
    class StaticPolygonShape : public IShape {
    public:
        u32 size = 3;
        fv2 points[4];
        float invDists[4];

        StaticPolygonShape() = default;
        StaticPolygonShape(Span<const fv2> ps);

        i32 WrapIndexUp(i32 i) const;
        i32 WrapIndexDown(i32 i) const;
        void SetPointsUnsafe(Span<const fv2> ps);
        void SetPointAt(const fv2& point, i32 i);

        const fv2& PointAt(i32 i) const { return points[i]; }
        fv2& PointAt(i32 i) { return points[i]; }
        float InvLenBtwn(i32 i) const { return invDists[i]; }
        float& InvLenBtwn(i32 i) { return invDists[i]; }

        void FixPolygon();
        fv2 CalcCentroid() const;
        void FixCentroid();
        void FixCentroid(const fv2& centroid);

        float ComputeArea() const;
        fRect2D ComputeBoundingBox() const;
        float Inertia() const;

        fv2 NearestPointTo(const fv2& point) const;
        fv2 FurthestAlong(const fv2& normal) const;
        fLine2D BestEdgeFor(const fv2& normal) const;
        fRange ProjectOntoAxis(const fv2& axis) const;
        fRange ProjectOntoOwnAxis(u32 axisID, const fv2& axis) const;
        bool AddSeperatingAxes(SeperatingAxisSolver& sat) const;
    };

    class DynPolygonShape : public IShape {
    public:
        struct PPoint {
            fv2 pos;
            fv2 nrm;
        };
        fv2 centroid = 0;
        Vec<PPoint> data;
    private:
        DynPolygonShape(Vec<PPoint>&& d) : data(std::move(d)) {}
    public:
        DynPolygonShape() = default;
        DynPolygonShape(Span<const fv2> points);
        DynPolygonShape(const DynPolygonShape& s) : data(s.data.Clone()) {}
        DynPolygonShape& operator=(const DynPolygonShape& s) { data = s.data.Clone(); return *this; }

        i32 WrapIndexUp(i32 i) const;
        i32 WrapIndexDown(i32 i) const;

        void SetPointsUnsafe(Span<const fv2> points);

        u32 Size() const { return data.Length(); }
        void AddPoint(const fv2& p);
        void AddPoint(const fv2& p, u32 i);
        void RemovePoint(u32 i);
        void PopPoint();
        void SetPoint(const fv2& p, i32 i);

        void FixPolygon();
        fv2 CalcCentroid();
        void FixCentroid();
        void FixCentroid(const fv2& centroid);

        float ComputeArea() const;
        fRect2D ComputeBoundingBox() const;
        float Inertia() const;

        fv2 NearestPointTo(const fv2& point) const;
        fv2 FurthestAlong(const fv2& normal) const;
        fLine2D BestEdgeFor(const fv2& normal) const;
        fRange ProjectOntoAxis(const fv2& axis) const;
        fRange ProjectOntoOwnAxis(u32 axisID, const fv2& axis) const;
        bool AddSeperatingAxes(SeperatingAxisSolver& sat) const;

        const fv2& PointAt(i32 i)  const { return data[i].pos; }
        fv2&       PointAt(i32 i)        { return data[i].pos; }
        const fv2& NormalAt(i32 i) const { return data[i].nrm; }
        fv2&       NormalAt(i32 i)       { return data[i].nrm; }
    };
} // Quasi
