#include "Collision2D.h"

#include <bits/stl_algo.h>

#include "Body2D.h"
#include "SeperatingAxisSolver.h"
#include "Utils/Debug/Logger.h"
#include "Utils/Math/Geometry.h"

namespace Quasi::Physics2D {
    float ClosestBetweenSegments(const fv2& a1, const fv2& b1, const fv2& a2, const fv2& b2,
                                 float* s, float* t, fv2* c1, fv2* c2) {
        const fv2 direction1 = b1 - a1; // Direction vector of segment S1
        const fv2 direction2 = b2 - a2; // Direction vector of segment S2
        const fv2 relative = a1 - a2;
        const float len1 = direction1.LenSq(); // Squared length of segment S1, always nonnegative
        const float len2 = direction2.LenSq(); // Squared length of segment S2, always nonnegative
        const float r2 = direction2.Dot(relative);

        // Check if either or both segments degenerate into points
        if (len1 <= f32s::DELTA && len2 <= f32s::DELTA) {
            // Both segments degenerate into points
            *s = *t = 0.0f;
            *c1 = a1;
            *c2 = a2;
            return c1->DistSq(*c2);
        }
        if (len1 <= f32s::DELTA) {
            // First segment degenerates into a point
            *s = 0.0f;
            *t = r2 / len2; // s = 0 => t = (b*s + f) / e = f / e
            *t = std::clamp(*t, 0.0f, 1.0f);
        } else {
            const float r1 = direction1.Dot(relative);
            if (len2 <= f32s::DELTA) {
                // Second segment degenerates into a point
                *t = 0.0f;
                *s = std::clamp(-r1 / len1, 0.0f, 1.0f); // t = 0 => s = (b*t - c) / a = -c / a
            } else {
                // The general nondegenerate case starts here
                const float b = direction1.Dot(direction2);
                const float denom = len1 * len2 - b * b; // Always nonnegative
                // If segments not parallel, compute closest point on L1 to L2 and
                // clamp to segment S1. Else pick arbitrary s (here 0)
                if (denom != 0.0f) {
                    *s = std::clamp((b * r2 - r1 * len2) / denom, 0.0f, 1.0f);
                } else *s = 0.0f;
                // Compute point on L2 closest to S1(s) using
                // t = Dot((P1 + D1*s) - P2,D2) / Dot(D2,D2) = (b*s + f) / e
                *t = (b * *s + r2) / len2;
                // If t in [0,1] done. Else clamp t, recompute s for the new value
                // of t using s = Dot((P2 + D2*t) - P1,D1) / Dot(D1,D1)= (t*b - c) / a
                // and clamp s to [0, 1]
                if (*t < 0.0f) {
                    *t = 0.0f;
                    *s = std::clamp(-r1 / len1, 0.0f, 1.0f);
                } else if (*t > 1.0f) {
                    *t = 1.0f;
                    *s = std::clamp((b - r1) / len1, 0.0f, 1.0f);
                }
            }
        }
        *c1 = a1 + direction1 * *s;
        *c2 = a2 + direction2 * *t;
        return c1->DistSq(*c2);
    }

    Manifold CollideShapes(const Shape& s1, const Pose2D& xf1, const Shape& s2, const Pose2D& xf2) {
        const Shape::ClipPrimitive prim1 = s1.PreferedPrimitive(),
                                   prim2 = s2.PreferedPrimitive();

#define SHAPE_PRIM_PAIR(X, Y) case Shape::PRIM_##X * 3 + Shape::PRIM_##Y
        switch (prim1 * 3 + prim2) {
            SHAPE_PRIM_PAIR(CIRCLE, CIRCLE):
                return CollideCircles(s1.As<CircleShape>(), xf1, s2.As<CircleShape>(), xf2);

            SHAPE_PRIM_PAIR(CIRCLE, LINE):  SHAPE_PRIM_PAIR(CIRCLE, POLYGON):
                return CollideCircleShape(s1, xf1, s2, xf2);

            SHAPE_PRIM_PAIR(LINE, CIRCLE): SHAPE_PRIM_PAIR(POLYGON, CIRCLE):
                return Manifold::Flip(CollideCircleShape(s2, xf2, s1, xf1));

            SHAPE_PRIM_PAIR(LINE, LINE):
                return CollideCapsules(s1, xf1, s2, xf2);

            SHAPE_PRIM_PAIR(POLYGON, LINE):
                return CollidePolygonCapsule(s1, xf1, s2, xf2);

            SHAPE_PRIM_PAIR(LINE, POLYGON):
                return Manifold::Flip(CollidePolygonCapsule(s2, xf2, s1, xf1));

            SHAPE_PRIM_PAIR(POLYGON, POLYGON):
                return CollidePolygons(s1, xf1, s2, xf2);

            default:
                return Manifold::None();
        }
    }

    Manifold CollideCircles(const CircleShape& s1, const Pose2D& xf1, const CircleShape& s2, const Pose2D& xf2) {
        float distsq = xf1.pos.DistSq(xf2.pos);
        if (distsq >= (s1.radius + s2.radius) * (s1.radius + s2.radius))
            return Manifold::None();

        distsq = std::sqrt(distsq);
        const fv2 n = (xf2.pos - xf1.pos) / distsq;
        return Manifold {
            .seperatingNormal = n,
            .contactPoint = { xf1.pos - n * s2.radius },
            .contactDepth = { s1.radius + s2.radius - distsq },
            .contactCount = 1,
        };
    }

    Manifold CollideCircleShape(const Shape& s1, const Pose2D& xf1, const Shape& s2, const Pose2D& xf2) {
        SeperatingAxisSolver sat = SeperatingAxisSolver::CheckCollisionFor(s1, xf1, s2, xf2);
        const auto& circle = *s1.As<CircleShape>();

        sat.SetCheckFor(SeperatingAxisSolver::NEITHER);
        sat.CheckAxis(xf2.Mul(s2.NearestPointTo(xf2.MulInv(xf1.pos))).Tangent(xf1.pos));

        sat.CheckAxisFor(SeperatingAxisSolver::TARGET);

        if (!sat.Collides())
            return Manifold::None();

        return Manifold {
            .seperatingNormal = sat.GetSepAxis(),
            .contactPoint = { xf1.pos + sat.GetSepAxis() * circle.radius },
            .contactDepth = { sat.GetDepth() },
            .contactCount = 1,
        };
    }

    Manifold CollidePolygons(const Shape& s1, const Pose2D& xf1, const Shape& s2, const Pose2D& xf2) {
        SeperatingAxisSolver sat = SeperatingAxisSolver::CheckCollisionFor(s1, xf1, s2, xf2);
        sat.CheckAxisFor(SeperatingAxisSolver::BASE);
        sat.CheckAxisFor(SeperatingAxisSolver::TARGET);

        if (!sat.Collides())
            return Manifold::None();

        return Manifold::From(sat);
    }

    Manifold CollideCapsules(const Shape& s1, const Pose2D& xf1, const Shape& s2, const Pose2D& xf2) {
        const CapsuleShape& cap1 = s1.As<CapsuleShape>(),
                          & cap2 = s2.As<CapsuleShape>();
        SeperatingAxisSolver sat = SeperatingAxisSolver::CheckCollisionFor(s1, xf1, s2, xf2);

        const fv2 f1 = xf1.MulD(cap1.forward),
                  f2 = xf2.MulD(cap2.forward);

        const fv2 off = xf1.pos - xf2.pos;
        const fv2 tip1 =  off + f1, end1 =  off - f1,
                  tip2 = -off + f2, end2 = -off - f2;
        const fv2 axis1 = tip1 - f2 * std::clamp(tip1.Dot(f2) * cap2.invLenSq, -1.0f, 1.0f),
                  axis2 = end1 - f2 * std::clamp(end1.Dot(f2) * cap2.invLenSq, -1.0f, 1.0f),
                  axis3 = tip2 - f1 * std::clamp(tip2.Dot(f1) * cap1.invLenSq, -1.0f, 1.0f),
                  axis4 = end2 - f1 * std::clamp(end2.Dot(f1) * cap1.invLenSq, -1.0f, 1.0f);

        sat.SetCheckFor(SeperatingAxisSolver::NEITHER);

        bool useSecondCapsule = false;

        sat.CheckAxis(axis1.Norm());
        sat.CheckAxis(axis2.Norm());
        useSecondCapsule |= sat.CheckAxis(axis3.Norm());
        useSecondCapsule |= sat.CheckAxis(axis4.Norm());

        if (!sat.Collides())
            return Manifold::None();

        return Manifold {
            .seperatingNormal = sat.GetSepAxis(),
            .contactPoint = {
                useSecondCapsule ?
                xf2.Mul(cap2.FurthestAlong(xf2.MulInvD(-sat.GetSepAxis()))) :
                xf1.Mul(cap1.FurthestAlong(xf1.MulInvD( sat.GetSepAxis())))
            },
            .contactDepth = { sat.GetDepth() },
            .contactCount = 1,
        };
    }

    Manifold CollidePolygonCapsule(const Shape& s1, const Pose2D& xf1, const Shape& s2, const Pose2D& xf2) {
        SeperatingAxisSolver sat = SeperatingAxisSolver::CheckCollisionFor(s1, xf1, s2, xf2);
        sat.CheckAxisFor(SeperatingAxisSolver::BASE);
        sat.CheckAxisFor(SeperatingAxisSolver::TARGET);

        const auto& cap = *s2.As<CapsuleShape>();
        sat.SetCheckFor(SeperatingAxisSolver::NEITHER);
        const fv2 tip = xf2.Mul(cap.forward), end = 2 * xf2.pos - tip;
        sat.CheckAxis(xf1.Mul(s1.NearestPointTo(xf1.MulInv(tip))).Tangent(tip));
        sat.CheckAxis(xf1.Mul(s1.NearestPointTo(xf1.MulInv(end))).Tangent(end));

        if (!sat.Collides())
            return Manifold::None();

        return Manifold {
            .seperatingNormal = sat.GetSepAxis(),
            .contactPoint = { xf2.Mul(cap.FurthestAlong(xf2.MulInvD(-sat.GetSepAxis()))) },
            .contactDepth = { sat.GetDepth() },
            .contactCount = 1,
        };
    }

    bool OverlapShapes(const Shape& s1, const Pose2D& xf1, const Shape& s2, const Pose2D& xf2) {
        const Shape::ClipPrimitive prim1 = s1.PreferedPrimitive(),
                                   prim2 = s2.PreferedPrimitive();

        switch (prim1 * 3 + prim2) {
            SHAPE_PRIM_PAIR(CIRCLE, CIRCLE):
                return OverlapCircles(s1.As<CircleShape>(), xf1, s2.As<CircleShape>(), xf2);

            SHAPE_PRIM_PAIR(CIRCLE, LINE):  SHAPE_PRIM_PAIR(CIRCLE, POLYGON):
                return OverlapCircleShape(s1, xf1, s2, xf2);

            SHAPE_PRIM_PAIR(LINE, CIRCLE): SHAPE_PRIM_PAIR(POLYGON, CIRCLE):
                return OverlapCircleShape(s2, xf2, s1, xf1);

            SHAPE_PRIM_PAIR(LINE, LINE):
                return OverlapCapsules(s1, xf1, s2, xf2);

            SHAPE_PRIM_PAIR(POLYGON, LINE):
                return OverlapPolygonCapsule(s1, xf1, s2, xf2);

            SHAPE_PRIM_PAIR(LINE, POLYGON):
                return OverlapPolygonCapsule(s2, xf2, s1, xf1);

            SHAPE_PRIM_PAIR(POLYGON, POLYGON):
                return OverlapPolygons(s1, xf1, s2, xf2);

            default:
                return false;
        }
    }

    bool OverlapCircles(const CircleShape& s1, const Pose2D& xf1, const CircleShape& s2, const Pose2D& xf2) {
        return xf1.pos.InRange(xf2.pos, s1.radius + s2.radius);
    }

    bool OverlapCircleShape(const Shape& s1, const Pose2D& xf1, const Shape& s2, const Pose2D& xf2) {
        SeperatingAxisSolver sat = SeperatingAxisSolver::CheckOverlapFor(s1, xf1, s2, xf2);
        sat.CheckAxisFor(SeperatingAxisSolver::TARGET);
        sat.SetCheckFor(SeperatingAxisSolver::NEITHER);
        sat.CheckAxis(xf2.Mul(s2.NearestPointTo(xf2.MulInv(xf1.pos))).Tangent(xf1.pos));
        return sat.Collides();
    }

    bool OverlapPolygons(const Shape& s1, const Pose2D& xf1, const Shape& s2, const Pose2D& xf2) {
        SeperatingAxisSolver sat = SeperatingAxisSolver::CheckCollisionFor(s1, xf1, s2, xf2);
        sat.CheckAxisFor(SeperatingAxisSolver::BASE);
        sat.CheckAxisFor(SeperatingAxisSolver::TARGET);

        return sat.Collides();
    }

    bool OverlapCapsules(const Shape& s1, const Pose2D& xf1, const Shape& s2, const Pose2D& xf2) {
        const CapsuleShape& cap1 = s1.As<CapsuleShape>(),
                          & cap2 = s2.As<CapsuleShape>();
        const auto [p1, p2] = fLine2D        { xf1.pos - cap1.forward, xf1.pos + cap1.forward }
                             .NearestBetween({ xf2.pos - cap2.forward, xf2.pos + cap2.forward });
        return p1.InRange(p2, cap1.radius + cap2.radius);
    }

    bool OverlapPolygonCapsule(const Shape& s1, const Pose2D& xf1, const Shape& s2, const Pose2D& xf2) {
        SeperatingAxisSolver sat = SeperatingAxisSolver::CheckCollisionFor(s1, xf1, s2, xf2);
        sat.CheckAxisFor(SeperatingAxisSolver::BASE);
        sat.CheckAxisFor(SeperatingAxisSolver::TARGET);

        const auto& cap = *s2.As<CapsuleShape>();
        sat.SetCheckFor(SeperatingAxisSolver::NEITHER);
        const fv2 tip = xf2.Mul(cap.forward), end = 2 * xf2.pos - tip;
        sat.CheckAxis(xf1.Mul(s1.NearestPointTo(xf1.MulInv(tip))).Tangent(tip));
        sat.CheckAxis(xf1.Mul(s1.NearestPointTo(xf1.MulInv(end))).Tangent(end));

        return sat.Collides();
    }

    void StaticResolve(Body& body, Body& target, const Manifold& manifold) {
        // if (manifold.flipped)
        //     std::swap(body, target);
        const bool bodyDyn   = body.IsDynamic(),
                   targetDyn = target.IsDynamic(),
                   shareForce = bodyDyn && targetDyn;
        fv2 sep = manifold.seperatingNormal;
        switch (manifold.contactCount) {
            case 0: return;
            case 1: {
                sep *= shareForce ? 0.5f * manifold.contactDepth[0] : manifold.contactDepth[0];
                if (bodyDyn)
                    body.position -= sep;
                if (targetDyn)
                    target.position += sep;
                break;
            }
            case 2: {
                const float depth = std::max(manifold.contactDepth[0], manifold.contactDepth[1]);
                sep *= shareForce ? 0.5f * depth : depth;
                if (bodyDyn)
                    body.position -= sep;
                if (targetDyn)
                    target.position += sep;
            }
            default: return;
        }
    }

    void DynamicResolve(Body& body, Body& target, const Manifold& manifold) {
        constexpr auto TAG = [] (const u32 ccount, bool bdyn, bool tdyn) constexpr -> u32 {
            return ccount << 2 |
                   bdyn << 1 |
                   tdyn;
        };

        switch (TAG(manifold.contactCount, body.IsDynamic(), target.IsDynamic())) {
            case TAG(1, true,  true ): DynamicResolveFor<1, true,  true >(body, target, manifold); break;
            case TAG(1, true,  false): DynamicResolveFor<1, true,  false>(body, target, manifold); break;
            case TAG(1, false, true ): DynamicResolveFor<1, false, true >(body, target, manifold); break;
            case TAG(2, true,  true ): DynamicResolveFor<2, true,  true >(body, target, manifold); break;
            case TAG(2, true,  false): DynamicResolveFor<2, true,  false>(body, target, manifold); break;
            case TAG(2, false, true ): DynamicResolveFor<2, false, true >(body, target, manifold); break;
            default: Debug::QError$("bad collision response");
        }
    }

    template <u32 ContactCount, bool BDyn, bool TDyn>
    void DynamicResolveFor(Body& body, Body& target, const Manifold& manifold) {
        const fv2& normal = manifold.seperatingNormal, tangent = normal.PerpendRight();
        const float share = ContactCount == 2 ? 0.5f : 1.0f;
        // this makes contactCount known in compile time for loop unrolling

        // if (relativeVelocity.dot(normal) > 0.0f) { // moving away from each other, dont collide
        //     return;
        // }

        constexpr float BODY_RESTITUION = 1.0f;
        constexpr float STATIC_FRICTION = 0.75f, DYNAMIC_FRICTION = 0.57f;

        fv2   relBody    [ContactCount], relTarget[ContactCount];
        float velocityMag[ContactCount], jn       [ContactCount];

        fv2 totalImpulse = 0;
        [[maybe_unused]] float totalBodyAngMtm = 0;
        [[maybe_unused]] float totalTargetAngMtm = 0;
        // normal forces
        for (u32 i = 0; i < ContactCount; ++i) {
            const fv2& contact = manifold.contactPoint[i];

            relBody  [i] = contact - body.position,
            relTarget[i] = contact - target.position;

            const fv2 relVel = [&] {
                if constexpr (BDyn && TDyn) {
                    const fv2 angularVelBody   = relBody  [i].PerpendLeft() * body.angularVelocity,
                              angularVelTarget = relTarget[i].PerpendLeft() * target.angularVelocity;

                    return (target.velocity + angularVelTarget) -
                           (body  .velocity + angularVelBody);
                } else if constexpr (BDyn) {
                    return -body.velocity - relBody[i].Perpend() * body.angularVelocity;
                } else /* targetDyn */ {
                    return target.velocity + relTarget[i].Perpend() * target.angularVelocity;
                }
            } ();

            velocityMag[i] = relVel.Dot(normal);
            if (velocityMag[i] > 0.0f) {
                jn[i] = 0;
                continue;
            }

            const float denomN = [&] {
                if constexpr (BDyn && TDyn) {
                    const float torqueRadiusNBody   = relBody  [i].Cross(normal),
                                torqueRadiusNTarget = relTarget[i].Cross(normal);

                    return body.invMass + target.invMass +
                          (torqueRadiusNBody   * torqueRadiusNBody)   * body  .invInertia +
                          (torqueRadiusNTarget * torqueRadiusNTarget) * target.invInertia;
                } else if constexpr (BDyn) {
                    const float torqueRadius = relBody[i].Cross(normal);
                    return body.invMass + torqueRadius * torqueRadius * body.invInertia;
                } else /* targetDyn */ {
                    const float torqueRadius = relTarget[i].Cross(normal);
                    return target.invMass + torqueRadius * torqueRadius * target.invInertia;
                }
            } ();

            jn[i] = -(1.0f + BODY_RESTITUION) * velocityMag[i] * share / denomN;

            const fv2 impulse = jn[i] * normal;

            totalImpulse      += impulse;
            if constexpr (BDyn) totalBodyAngMtm   -= relBody  [i].Cross(impulse);
            if constexpr (TDyn) totalTargetAngMtm += relTarget[i].Cross(impulse);
        }

        if constexpr (BDyn) {
            body.AddMomentum(-totalImpulse);
            body.AddAngularMomentum(totalBodyAngMtm);
        }
        if constexpr (TDyn) {
            target.AddMomentum(totalImpulse);
            target.AddAngularMomentum(totalTargetAngMtm);
        }

        totalImpulse = 0;
        totalBodyAngMtm = 0; totalTargetAngMtm = 0;
        // frictional forces (needs to be separated, order matters)
        for (u32 i = 0; i < ContactCount; ++i) {
            const fv2 relVel = [&] {
                if constexpr (BDyn && TDyn) {
                    const fv2 angularVelBody   = relBody  [i].PerpendLeft() * body.angularVelocity,
                              angularVelTarget = relTarget[i].PerpendLeft() * target.angularVelocity;

                    return (target.velocity + angularVelTarget) -
                           (body  .velocity + angularVelBody);
                } else if constexpr (BDyn) {
                    return -body.velocity - relBody[i].Perpend() * body.angularVelocity;
                } else /* targetDyn */ {
                    return target.velocity + relTarget[i].Perpend() * target.angularVelocity;
                }
            } ();

            const float t = relVel.Dot(tangent);

            if (std::abs(t) <= f32s::DELTA) continue;

            const float denomT = [&] {
                if constexpr (BDyn && TDyn) {
                    const float torqueRadiusTBody   = relBody  [i].Cross(tangent),
                                torqueRadiusTTarget = relTarget[i].Cross(tangent);

                    return body.invMass + target.invMass +
                          (torqueRadiusTBody   * torqueRadiusTBody)   * body  .invInertia +
                          (torqueRadiusTTarget * torqueRadiusTTarget) * target.invInertia;
                } else if constexpr (BDyn) {
                    const float torqueRadius = relBody[i].Cross(tangent);
                    return body.invMass + torqueRadius * torqueRadius * body.invInertia;
                } else /* targetDyn */ {
                    const float torqueRadius = relTarget[i].Cross(tangent);
                    return target.invMass + torqueRadius * torqueRadius * target.invInertia;
                }
            } ();

            const float jt = -t * share / denomT;
            const fv2 frictionImpulse = tangent * (
                std::abs(jt) <= std::abs(jn[i] * STATIC_FRICTION) ?
                jt : (jt < 0 ? -1.0f : 1.0f) * jn[i] * DYNAMIC_FRICTION
            ); // static/dynamic friction picking

            totalImpulse      += frictionImpulse;
            if constexpr (BDyn) totalBodyAngMtm   -= relBody  [i].Cross(frictionImpulse);
            if constexpr (TDyn) totalTargetAngMtm += relTarget[i].Cross(frictionImpulse);
        }

        if constexpr (BDyn) {
            body.AddMomentum(-totalImpulse);
            body.AddAngularMomentum(totalBodyAngMtm);
        }
        if constexpr (TDyn) {
            target.AddMomentum(totalImpulse);
            target.AddAngularMomentum(totalTargetAngMtm);
        }
    }

    template void DynamicResolveFor<1, true,  true >(Body& body, Body& target, const Manifold& manifold);
    template void DynamicResolveFor<1, true,  false>(Body& body, Body& target, const Manifold& manifold);
    template void DynamicResolveFor<1, false, true >(Body& body, Body& target, const Manifold& manifold);
    template void DynamicResolveFor<2, true,  true >(Body& body, Body& target, const Manifold& manifold);
    template void DynamicResolveFor<2, true,  false>(Body& body, Body& target, const Manifold& manifold);
    template void DynamicResolveFor<2, false, true >(Body& body, Body& target, const Manifold& manifold);
} // Physics2D