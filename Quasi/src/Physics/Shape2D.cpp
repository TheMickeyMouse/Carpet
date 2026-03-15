#include "Shape2D.h"

namespace Quasi::Physics2D {
    using namespace Math;
#define IMPLEMENT_SHAPE_FN(R, K, N, PARAMS, ARGS) R K::N PARAMS const { return Visit<R>([&] (const auto& s) { return s.N ARGS; }); }

    IMPLEMENT_SHAPE_FN(float,    Shape, ComputeArea,        (), ())
    IMPLEMENT_SHAPE_FN(fRect2D,  Shape, ComputeBoundingBox, (), ())
    IMPLEMENT_SHAPE_FN(float,    Shape, Inertia,            (), ())
    IMPLEMENT_SHAPE_FN(fv2,      Shape, NearestPointTo,     (const fv2& point),            (point))
    IMPLEMENT_SHAPE_FN(fv2,      Shape, FurthestAlong,      (const fv2& normal),           (normal))
    IMPLEMENT_SHAPE_FN(fLine2D,  Shape, BestEdgeFor,        (const fv2& normal),           (normal))
    IMPLEMENT_SHAPE_FN(fRange,   Shape, ProjectOntoAxis,    (const fv2& axis),             (axis))
    IMPLEMENT_SHAPE_FN(fRange,   Shape, ProjectOntoOwnAxis, (u32 axisID, const fv2& axis), (axisID, axis))
    IMPLEMENT_SHAPE_FN(bool,     Shape, AddSeperatingAxes,  (SeperatingAxisSolver& sat),        (sat))

    Shape MakePolygon(Span<const fv2> points) {
        switch (points.Length()) {
            case 3:
            case 4:  return StaticPolygonShape { points };
            default: return DynPolygonShape { points };
        }
    }
} // Quasi