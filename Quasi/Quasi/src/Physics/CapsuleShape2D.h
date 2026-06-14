#pragma once
#include "IShape2D.h"
#include "Utils/Math/Rect.h"
#include "Utils/Math/Vector.h"

namespace Quasi::Physics2D {
    class CapsuleShape : public IShape {
    public:
        fv2 forward;
        float length = 1.0f, invLength = 1.0f, invLenSq;
        float radius = 0.0f;

        CapsuleShape(const fv2& fwd, float r)
            : forward(fwd), length(fwd.Len()), invLength(1.0f / length), invLenSq(invLength * invLength), radius(r) {}

        float ComputeArea() const;
        fRect2D ComputeBoundingBox() const;
        float Inertia() const;

        fv2 NearestPointTo(const fv2& point) const;
        fv2 FurthestAlong(const fv2& normal) const;
        fRange ProjectOntoAxis(const fv2& axis) const;
        fRange ProjectOntoOwnAxis(u32 axisID, const fv2& axis) const;
        bool AddSeperatingAxes(SeperatingAxisSolver& sat) const;

        void SetForward(const fv2& f);
    };
} // Quasi
