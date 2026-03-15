#include "Manifold2D.h"

#include "SeperatingAxisSolver.h"
#include "Shape2D.h"

namespace Quasi::Physics2D {
    Manifold Manifold::None() {
        return {
            .contactCount = 0
        };
    }

    Manifold Manifold::From(const SeperatingAxisSolver& sat) {
        const Shape&  base = sat.base, & target = sat.target;
        const Pose2D& bXf  = sat.baseXf, tXf    = sat.targetXf;
        const fv2& n = sat.seperatingAxis;

        static constexpr auto MulLine = [] (const Pose2D& xf, const fLine2D& l) {
            return fLine2D::FromDirection(xf.Mul(l.start), xf.MulD(l.forward));
        };

        const fLine2D baseClips   = MulLine(bXf, base  .BestEdgeFor(bXf.MulInvD(n))),
                      targetClips = MulLine(tXf, target.BestEdgeFor(tXf.MulInvD(-n)));

        const bool flip = std::abs(baseClips.forward.Dot(n)) > std::abs(targetClips.forward.Dot(n));
        const fLine2D& ref = flip ? targetClips : baseClips, &inc = flip ? baseClips : targetClips;

        Manifold manifold = FromEdges(ref, inc, flip ? n : -n);
        manifold.seperatingNormal = n;
        // return the valid points
        return manifold;
    }

    Manifold Manifold::FromEdges(const fLine2D& ref, const fLine2D& inc, const fv2& n) {
        const fv2 refFwd = ref.forward.Norm();

        Manifold manifold = Clip(inc.start, inc.End(), refFwd, refFwd.Dot(ref.start));

        manifold = Clip(manifold.contactPoint[0], manifold.contactPoint[1], -refFwd, -refFwd.Dot(ref.End()));

        Manifold result = None();
        const fv2 refNorm = n;
        const float max = ref.start.Dot(refNorm);

        if (const float d = refNorm.Dot(manifold.contactPoint[0]) - max; d > 0) {
            result.AddPoint(manifold.contactPoint[0], d);
        }
        if (const float d = refNorm.Dot(manifold.contactPoint[1]) - max; d > 0) {
            result.AddPoint(manifold.contactPoint[1], d);
        }
        // return the valid points
        return result;
    }

    Manifold Manifold::Clip(const fv2& v0, const fv2& v1, const fv2& normal, float threshold) {
        const float d0 = v0.Dot(normal) - threshold, d1 = v1.Dot(normal) - threshold;

        Manifold manifold {};

        if (d0 >= 0.0f) // correct sides
            manifold.AddPoint(v0);
        if (d1 >= 0.0f) // correct sides
            manifold.AddPoint(v1);

        if (d0 * d1 < 0.0f) { // different sides
            manifold.AddPoint(fLine2D { v0, v1 - v0 }.Lerp(d0 / (d0 - d1)));
        }

        return manifold;
    }

    void Manifold::Invert() {
        seperatingNormal = -seperatingNormal;
    }

    Manifold Manifold::Flip(Manifold&& m) {
        m.Invert();
        return m;
    }

    void Manifold::AddPoint(const fv2& point, float depth) {
        contactPoint[contactCount] = point;
        contactDepth[contactCount] = depth;
        ++contactCount;
    }
} // Quasi