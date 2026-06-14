#include "CircleShape2D.h"

namespace Quasi::Physics2D {
    float CircleShape::ComputeArea() const {
        return PI * radius * radius;
    }

    fRect2D CircleShape::ComputeBoundingBox() const {
        return { -radius, radius };
    }

    float CircleShape::Inertia() const {
        return 0.5f * radius * radius;
    }

    fv2 CircleShape::NearestPointTo(const fv2& point) const {
        return point.Norm(radius);
    }

    fv2 CircleShape::FurthestAlong(const fv2& normal) const {
        return normal * radius;
    }

    fRange CircleShape::ProjectOntoAxis(const fv2&) const {
        return { -radius, +radius };
    }

    fRange CircleShape::ProjectOntoOwnAxis(u32, const fv2& axis) const {
        return ProjectOntoAxis(axis);
    }
} // Quasi