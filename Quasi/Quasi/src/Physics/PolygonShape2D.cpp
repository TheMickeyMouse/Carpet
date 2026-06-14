#include "PolygonShape2D.h"

#include "SeperatingAxisSolver.h"

namespace Quasi::Physics2D {
    StaticPolygonShape::StaticPolygonShape(Span<const fv2> ps) {
        SetPointsUnsafe(ps);
    }

    i32 StaticPolygonShape::WrapIndexUp(i32 i) const {
        ++i;
        return i >= size ? i - size : i;
    }

    i32 StaticPolygonShape::WrapIndexDown(i32 i) const {
        --i;
        return i < 0 ? (i32)size + i : i;
    }

    void StaticPolygonShape::SetPointsUnsafe(Span<const fv2> ps) {
        size = std::min<u32>(ps.Length(), 4);
        points[0] = ps[0];
        invDists[0] = 1 / ps[0].Dist(ps[size - 1]);
        for (u32 i = 1; i < size; ++i) {
            points[i]   = ps[i];
            invDists[i] = 1 / ps[i].Dist(ps[i - 1]);
        }
    }

    void StaticPolygonShape::SetPointAt(const fv2& point, i32 i) {
        points[i] = point;
        invDists[i] = 1 / points[i].Dist(points[WrapIndexDown(i)]);
        const i32 j = WrapIndexUp(i);
        invDists[j] = 1 / points[j].Dist(points[i]);
    }

    void StaticPolygonShape::FixPolygon() {
        invDists[0] = 1 / points[0].Dist(points[size - 1]);
        for (u32 i = 1; i < size; ++i) {
            invDists[i] = 1 / points[i].Dist(points[i - 1]);
        }
    }

    fv2 StaticPolygonShape::CalcCentroid() const {
        if (size == 3) {
            return (points[0] + points[1] + points[2]) * (1 / 3.0f);
        }
        float x = 0.0f, y = 0.0f, area = 0.0f;
        u32 i = 0;
        for (; i < size - 1; i++) {
            const fv2& p0 = points[i], &p1 = points[i + 1];
            const float areaSum = (p0.x * p1.y) - (p1.x * p0.y);

            x += (p0.x + p1.x) * areaSum;
            y += (p0.y + p1.y) * areaSum;
            area += areaSum;
        }
        // split modulo branch
        const fv2& p0 = points[i], &p1 = points[0];
        const float areaSum = (p0.x * p1.y) - (p1.x * p0.y);

        x += (p0.x + p1.x) * areaSum;
        y += (p0.y + p1.y) * areaSum;
        area += areaSum;

        const float invArea = 1.0f / 3.0f / area;
        return { x * invArea, y * invArea };
    }

    void StaticPolygonShape::FixCentroid() {
        FixCentroid(CalcCentroid());
    }

    void StaticPolygonShape::FixCentroid(const fv2& centroid) {
        for (u32 i = 0; i < size; ++i) {
            points[i] -= centroid;
        }
    }

    float StaticPolygonShape::ComputeArea() const {
        float area = 0;

        u32 i = 0;
        for (; i < size - 1; ++i)
            area += points[i].x * points[i + 1].y - points[i + 1].x * points[i].y;
        // split modulo branch
        area += points[i].x * points[0].y - points[0].x * points[i].y;

        return std::abs(area) / 2;
    }

    fRect2D StaticPolygonShape::ComputeBoundingBox() const {
        fRect2D rect = fRect2D::AntiDomain();
        for (u32 i = 0; i < size; ++i) rect.ExpandToFit(points[i]);
        return rect;
    }

    float StaticPolygonShape::Inertia() const {
        float inertNum = 0.0f, inertDen = 0.0f;
        u32 i = 0;
        for (; i < size - 1; ++i) {
            const float z = points[i + 1].Cross(points[i]);
            inertDen += z;
            const float uSquared = points[i].LenSq(), vSquared = points[i + 1].LenSq();
            inertNum += z * (uSquared + vSquared + std::sqrt(uSquared * vSquared));
        }
        return inertNum / (inertDen * 6);
    }

    fv2 StaticPolygonShape::NearestPointTo(const fv2& point) const {
        u32 nearest = 0;
        float mindist = point.DistSq(points[0]);
        for (u32 i = 1; i < size; ++i) {
            if (const float d = point.DistSq(points[i]); d < mindist) {
                mindist = d;
                nearest = i;
            }
        }
        return points[nearest];
    }

    fv2 StaticPolygonShape::FurthestAlong(const fv2& normal) const {
        u32 furthest = 0;
        float m = normal.Dot(points[0]);
        for (u32 i = 1; i < size; ++i) {
            if (const float d = normal.Dot(points[i]); d > m) {
                m = d;
                furthest = i;
            }
        }
        return points[furthest];
    }

    fLine2D StaticPolygonShape::BestEdgeFor(const fv2& normal) const {
        float maxDepth = normal.Dot(points[0]);
        i32 furthest = 0;
        for (i32 i = 1; i < size; ++i) {
            if (const float d = normal.Dot(points[i]); d > maxDepth) {
                maxDepth = d;
                furthest = i;
            }
        }

        const i32 i0 = WrapIndexUp(furthest), i1 = WrapIndexDown(furthest);
        const fv2 &p  = points[furthest],
                   f0 = points[i0] - p,
                   f1 = points[i1] - p;
        if (std::abs(f0.Dot(normal)) * invDists[i0] >
            std::abs(f1.Dot(normal)) * invDists[i1])
            return { p, f1 };
        return { p, f0 };
    }

    fRange StaticPolygonShape::ProjectOntoAxis(const fv2& axis) const {
        fRange range = fRange::AntiDomain();
        for (u32 i = 0; i < size; ++i) {
            const float d = axis.Dot(points[i]);
            range.ExpandToFit(d);
        }
        return range;
    }

    fRange StaticPolygonShape::ProjectOntoOwnAxis(u32 axisID, const fv2& axis) const {
        fRange range = fRange::On(axis.Dot(points[axisID]));
        for (u32 i = 0; i < size; ++i) {
            if (i == axisID || i == WrapIndexUp(axisID)) continue;
            const float d = axis.Dot(points[i]);
            range.ExpandToFit(d);
        }
        return range;
    }

    bool StaticPolygonShape::AddSeperatingAxes(SeperatingAxisSolver& sat) const {
        bool success = false;
        u32 i = 0;
        for (; i < size - 1; ++i) {
            success |= sat.CheckAxis((points[i + 1] - points[i]).PerpendLeft() * InvLenBtwn(i));
        }
        success |= sat.CheckAxis((points[0] - points[i]).PerpendLeft() * InvLenBtwn(i));
        return success;
    }
    
    DynPolygonShape::DynPolygonShape(Span<const fv2> points) : data(Vec<PPoint>::WithCap(points.Length())) {
        SetPointsUnsafe(points);
        FixCentroid();
    }

    i32 DynPolygonShape::WrapIndexUp(i32 i) const {
        ++i;
        return i == data.Length() ? 0 : i;
    }

    i32 DynPolygonShape::WrapIndexDown(i32 i) const {
        --i;
        return i < 0 ? (i32)data.Length() + i : i;
    }

    void DynPolygonShape::SetPointsUnsafe(Span<const fv2> points) {
        u32 i = 0;
        for (; i < points.Length() - 1; ++i) {
            data.Push({ points[i], points[i + 1].Tangent(points[i]).PerpendRight() });
        }
        data.Push({ points[i], points[i + 1].Tangent(points[i]).PerpendRight() });
    }

    void DynPolygonShape::AddPoint(const fv2& p) {
        data.Last().nrm = data.Last().pos.Tangent(p);
        data.Push({ p, p.Tangent(data[0].pos).PerpendRight() });
    }

    void DynPolygonShape::AddPoint(const fv2& p, u32 i) {
        // doesnt need i + 1 because length is not updated
        const i32 prev = WrapIndexDown((i32)i);
        data[prev].nrm = data[prev].pos.Tangent(p).PerpendRight();
        data.Insert({ p, p.Tangent(data[i].pos).PerpendRight() }, i);
    }

    void DynPolygonShape::RemovePoint(u32 i) {
        data.Pop(i);
        const i32 j = WrapIndexDown((i32)i);
        data[j].nrm = data[j].pos.Tangent(data[WrapIndexUp(j)].pos).PerpendRight();
    }

    void DynPolygonShape::PopPoint() {
        data.Pop();
        data.Last().nrm = data.Last().pos.Tangent(data[0].pos).PerpendRight();
    }

    void DynPolygonShape::SetPoint(const fv2& p, i32 i) {
        data[i].pos = p;
        const i32 j = WrapIndexDown((i32)i);
        data[j].nrm = data[j].pos.Tangent(p).PerpendRight();
    }

    void DynPolygonShape::FixPolygon() {
        for (u32 i = 0; i < data.Length(); ++i) {
            data[i].nrm = data[i].pos.Tangent(data[WrapIndexUp(i)].pos).PerpendRight();
        }
    }

    fv2 DynPolygonShape::CalcCentroid() {
        float x = 0.0f, y = 0.0f, area = 0.0f;
        u32 i = 0;
        for (; i < data.Length() - 1; i++) {
            const fv2& p0 = data[i].pos, &p1 = data[i + 1].pos;
            const float areaSum = (p0.x * p1.y) - (p1.x * p0.y);

            x += (p0.x + p1.x) * areaSum;
            y += (p0.y + p1.y) * areaSum;
            area += areaSum;
        }
        // split modulo branch
        const fv2& p0 = data[i].pos, &p1 = data[0].pos;
        const float areaSum = (p0.x * p1.y) - (p1.x * p0.y);

        x += (p0.x + p1.x) * areaSum;
        y += (p0.y + p1.y) * areaSum;
        area += areaSum;

        const float invArea = 1.0f / 3.0f / area;
        return { x * invArea, y * invArea };
    }

    void DynPolygonShape::FixCentroid() {
        FixCentroid(CalcCentroid());
    }

    void DynPolygonShape::FixCentroid(const fv2& centroid) {
        for (u32 i = 0; i < data.Length(); ++i) {
            data[i].pos -= centroid;
        }
    }

    float DynPolygonShape::ComputeArea() const {
        float area = 0;

        u32 i = 0;
        for (; i < data.Length() - 1; ++i)
            area += data[i].pos.x * data[i + 1].pos.y - data[i + 1].pos.x * data[i].pos.y;
        // split modulo branch
        area += data[i].pos.x * data[0].pos.y - data[0].pos.x * data[i].pos.y;

        return std::abs(area) / 2;
    }

    fRect2D DynPolygonShape::ComputeBoundingBox() const {
        fRect2D rect = fRect2D::AntiDomain();
        for (u32 i = 0; i < data.Length(); ++i) rect.ExpandToFit(data[i].pos);
        return rect;
    }

    float DynPolygonShape::Inertia() const {
        float inertNum = 0.0f, inertDen = 0.0f;
        u32 i = 0;
        for (; i < data.Length() - 1; ++i) {
            const float z = data[i + 1].pos.Cross(data[i].pos);
            inertDen += z;
            const float uSquared = data[i].pos.LenSq(), vSquared = data[i + 1].pos.LenSq();
            inertNum += z * (uSquared + vSquared + std::sqrt(uSquared * vSquared));
        }
        return inertNum / (inertDen * 6);
    }

    fv2 DynPolygonShape::NearestPointTo(const fv2& point) const {
        u32 nearest = 0;
        float mindist = point.DistSq(data[0].pos);
        for (u32 i = 1; i < data.Length(); ++i) {
            if (const float d = point.DistSq(data[i].pos); d < mindist) {
                mindist = d;
                nearest = i;
            }
        }
        return data[nearest].pos;
    }

    fv2 DynPolygonShape::FurthestAlong(const fv2& normal) const {
        u32 furthest = 0;
        float m = normal.Dot(data[0].pos);
        for (u32 i = 1; i < data.Length(); ++i) {
            if (const float d = normal.Dot(data[i].pos); d > m) {
                m = d;
                furthest = i;
            }
        }
        return data[furthest].pos;
    }

    fLine2D DynPolygonShape::BestEdgeFor(const fv2& normal) const {
        float maxDepth = normal.Dot(data[0].pos);
        i32 furthest = 0;
        for (i32 i = 1; i < data.Length(); ++i) {
            if (const float d = normal.Dot(data[0].pos); d > maxDepth) {
                maxDepth = d;
                furthest = i;
            }
        }

        const i32 i0 = WrapIndexUp(furthest), i1 = WrapIndexDown(furthest);
        const fv2 &p  = data[furthest].pos;
        if (std::abs(data[i1].nrm.Cross(normal)) >
            std::abs(data[i1].nrm.Cross(normal)))
            return { p, data[i1].pos - p };
        return { p, data[i0].pos - p };
    }

    fRange DynPolygonShape::ProjectOntoAxis(const fv2& axis) const {
        fRange range = fRange::AntiDomain();
        for (u32 i = 0; i < data.Length(); ++i) {
            const float d = axis.Dot(data[i].pos);
            range.ExpandToFit(d);
        }
        return range;
    }

    fRange DynPolygonShape::ProjectOntoOwnAxis(u32 axisID, const fv2& axis) const {
        fRange range = fRange::On(axis.Dot(data[axisID].pos));
        for (u32 i = 0; i < data.Length(); ++i) {
            if (i == axisID || i == WrapIndexUp(axisID)) continue;
            const float d = axis.Dot(data[i].pos);
            range.ExpandToFit(d);
        }
        return range;
    }

    bool DynPolygonShape::AddSeperatingAxes(SeperatingAxisSolver& sat) const {
        bool success = false;
        for (u32 i = 0; i < data.Length(); ++i) {
            success |= sat.CheckAxis(data[i].nrm);
        }
        return success;
    }
}
