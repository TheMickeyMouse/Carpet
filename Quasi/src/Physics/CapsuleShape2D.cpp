#include "CapsuleShape2D.h"

#include "SeperatingAxisSolver.h"

namespace Quasi::Physics2D {
    float CapsuleShape::ComputeArea() const {
        return radius * (PI * radius + length * 4);
    }

    float CapsuleShape::Inertia() const {
        // $$ m \frac {1} {4L + \pi r} (\frac {\pi r^3}{2} + \frac {L^3 + 4r^2L} {3}) $$
        const float rSquared = radius * radius;
        return (HALF_PI * rSquared * radius +
                length * (length * length + 4 * rSquared) / 3)
              / (PI * radius + 4 * length);
    }

    void CapsuleShape::SetForward(const fv2& f) {
        forward = f;
        length = f.Len();
        invLength = 1 / length;
        invLenSq = invLength * invLength;
    }

    fRect2D CapsuleShape::ComputeBoundingBox() const {
        return fRect2D { -forward, forward }.Fixed().Extrude(radius);
    }

    fv2 CapsuleShape::NearestPointTo(const fv2& point) const {
        const float t = Math::Clamp(forward.Dot(point) * invLenSq, -1.0f, 1.0f);
        const fv2 closest = forward * t;
        return closest + (point - closest).Norm(radius);
    }

    fv2 CapsuleShape::FurthestAlong(const fv2& normal) const {
        return (0 > forward.Dot(normal) ? -forward : forward) + normal * radius;
    }

    fRange CapsuleShape::ProjectOntoAxis(const fv2& axis) const {
        const float f = std::abs(forward.Dot(axis));
        return fRange { -f, f }.Extrude(radius);
    }

    fRange CapsuleShape::ProjectOntoOwnAxis(u32, const fv2&) const {
        return { -radius, +radius };
    }

    bool CapsuleShape::AddSeperatingAxes(SeperatingAxisSolver& sat) const {
        return sat.CheckAxis(forward.Perpend() * invLength);
    }
} // Quasi