#pragma once
#include "IShape2D.h"
#include "Utils/Math/Vector.h"

namespace Quasi::Physics2D {
    using namespace Math;

    class SeperatingAxisSolver;

    struct Manifold {
        fv2 seperatingNormal;
        fv2 contactPoint[2];
        float contactDepth[2];
        u32 contactCount = 0;

        static Manifold None();

        static Manifold From(const SeperatingAxisSolver& sat);
        static Manifold FromEdges(const fLine2D& ref, const fLine2D& inc, const fv2& n);

        static Manifold Clip(const fv2& v0, const fv2& v1,
                             const fv2& normal, float threshold);

        void Invert();
        static Manifold Flip(Manifold&& m);
        void AddPoint(const fv2& point, float depth = 0);
    };
} // Quasi
