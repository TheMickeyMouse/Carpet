#pragma once
#include "CapsuleShape2D.h"
#include "CircleShape2D.h"
#include "PolygonShape2D.h"
#include "RectShape2D.h"
#include "Utils/Match.h"

namespace Quasi::Physics2D {
    template <class T> static constexpr IShape::Type ShapeTypeIndexOf() {
        Qmatch$ ((typename)T, (
            case (CircleShape)        { return IShape::CIRCLE; },
            case (CapsuleShape)       { return IShape::CAPSULE; },
            case (RectShape)          { return IShape::RECT; },
            case (StaticPolygonShape) { return IShape::POLY_SMALL; },
            case (DynPolygonShape)    { return IShape::POLY; },
            else { static_assert(false, "oops"); return IShape::CIRCLE; }
        ));
    }
    static constexpr IShape::ClipPrimitive PrimitiveOfType(IShape::Type t) {
        return (IShape::ClipPrimitive)((t >= IShape::CAPSULE) + (t >= IShape::RECT));
    }

    class Shape :
        public IShape,
        public Variant<CircleShape, CapsuleShape, RectShape, StaticPolygonShape, DynPolygonShape> {
    public:
        Shape() : Variant(CircleShape { 0.0f }) {}
        Shape(Variant v) : Variant(std::move(v)) {}
        Shape(const Extends<IShape> auto& s) : Variant(s) {}
        Shape(Extends<IShape> auto&& s) : Variant(std::forward<decltype(s)>(s)) {}

        float ComputeArea() const;
        fRect2D ComputeBoundingBox() const;
        float Inertia() const;

        fv2 NearestPointTo(const fv2& point) const;
        fv2 FurthestAlong(const fv2& normal) const;
        fLine2D BestEdgeFor(const fv2& normal) const;
        fRange ProjectOntoAxis(const fv2& axis) const;
        fRange ProjectOntoOwnAxis(u32 axisID, const fv2& axis) const;
        bool AddSeperatingAxes(SeperatingAxisSolver& sat) const;

        Type TypeIndex() const { return (Type)GetTagImpl(); }
        ClipPrimitive PreferedPrimitive() const { return PrimitiveOfType(TypeIndex()); }
    };

    Shape MakePolygon(Span<const fv2> points);
} // Quasi
