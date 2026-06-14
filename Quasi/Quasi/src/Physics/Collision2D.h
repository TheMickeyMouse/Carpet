#pragma once
#include "Manifold2D.h"
#include "Utils/Math/Vector.h"
#include "Utils/Math/Transform2D.h"

namespace Quasi::Physics2D {
    class Shape;
    class CircleShape;
    class CapsuleShape;
    class Body;
}

namespace Quasi::Physics2D {
    using namespace Math;

    float ClosestBetweenSegments(const fv2& a1, const fv2& b1, const fv2& a2, const fv2& b2,
                                 float* s, float* t, fv2* c1, fv2* c2);

    Manifold CollideShapes(const Shape& s1, const Pose2D& xf1, const Shape& s2, const Pose2D& xf2);

    Manifold CollideCircles       (const CircleShape& s1, const Pose2D& xf1, const CircleShape& s2, const Pose2D& xf2);
    Manifold CollideCircleShape   (const Shape& s1,       const Pose2D& xf1, const Shape& s2,       const Pose2D& xf2);
    Manifold CollidePolygons      (const Shape& s1,       const Pose2D& xf1, const Shape& s2,       const Pose2D& xf2);
    Manifold CollideCapsules      (const Shape& s1,       const Pose2D& xf1, const Shape& s2,       const Pose2D& xf2);
    Manifold CollidePolygonCapsule(const Shape& s1,       const Pose2D& xf1, const Shape& s2,       const Pose2D& xf2);

    bool OverlapShapes(const Shape& s1, const Pose2D& xf1, const Shape& s2, const Pose2D& xf2);

    bool OverlapCircles       (const CircleShape& s1, const Pose2D& xf1, const CircleShape& s2, const Pose2D& xf2);
    bool OverlapCircleShape   (const Shape& s1,       const Pose2D& xf1, const Shape& s2,       const Pose2D& xf2);
    bool OverlapPolygons      (const Shape& s1,       const Pose2D& xf1, const Shape& s2,       const Pose2D& xf2);
    bool OverlapCapsules      (const Shape& s1,       const Pose2D& xf1, const Shape& s2,       const Pose2D& xf2);
    bool OverlapPolygonCapsule(const Shape& s1,       const Pose2D& xf1, const Shape& s2,       const Pose2D& xf2);

    void StaticResolve (Body& body, Body& target, const Manifold& manifold);
    template <u32 ContactCount, bool BDyn, bool TDyn>
    void DynamicResolveFor(Body& body, Body& target, const Manifold& manifold);
    void DynamicResolve(Body& body, Body& target, const Manifold& manifold);
} // Physics2D::Collision
