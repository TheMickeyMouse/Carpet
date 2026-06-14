#pragma once
#include "IShape2D.h"
#include "Utils/Math/Rect.h"

namespace Quasi::Physics2D {
    class CircleShape : public IShape {
    public:
        float radius = 1.0f;

        CircleShape(float r) : radius(r) {}
        float ComputeArea() const;
        fRect2D ComputeBoundingBox() const;
        float Inertia() const;

        fv2 NearestPointTo(const fv2& point) const;
        fv2 FurthestAlong(const fv2& normal) const;
        fRange ProjectOntoAxis(const fv2& axis) const;
        fRange ProjectOntoOwnAxis(u32 axisID, const fv2& axis) const;
        bool AddSeperatingAxes(SeperatingAxisSolver&) const { return false; }
    };
} // Quasi
