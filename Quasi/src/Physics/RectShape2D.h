#pragma once
#include "IShape2D.h"

namespace Quasi::Physics2D {
    class RectShape : public IShape {
    public:
        float hx, hy;

        RectShape(float x, float y) : hx(x), hy(y) {}

        fv2 Corner(bool px, bool py) const;

        float ComputeArea() const { return 4 * hx * hy; }
        fRect2D ComputeBoundingBox() const;
        float Inertia() const;

        fv2 NearestPointTo(const fv2& point) const;
        fv2 FurthestAlong(const fv2& normal) const;
        fLine2D BestEdgeFor(const fv2& normal) const;
        fRange ProjectOntoAxis(const fv2& axis) const;
        fRange ProjectOntoOwnAxis(u32 axisID, const fv2& axis) const;
        bool AddSeperatingAxes(SeperatingAxisSolver& sat) const;
    };
} // Quasi
