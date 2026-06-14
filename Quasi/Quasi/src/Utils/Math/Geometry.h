#pragma once

#include "Vector.h"

namespace Quasi::Math {
    // TODO: ADD MATH METHODS
    template <class VecT>
    struct Line {
        using T = decltype(VecT {}.x);
        VecT start, forward;

        Line() : start(), forward() {}
        Line(const VecT& v) : start(0), forward(v) {}
        Line(const VecT& s, const VecT& f) : start(s), forward(f) {}

        static Line FromDirection(const VecT& s, const VecT& f) { return { s, f }; }
        static Line FromPoints   (const VecT& s, const VecT& e) { return { s, e - s }; }

        VecT End() const { return start + forward; }

        Line  operator+ (const VecT& off) const { return { start + off, forward }; }
        Line& operator+=(const VecT& off)       { start += off; return *this; }
        Line  operator- (const VecT& off) const { return { start - off, forward }; }
        Line& operator-=(const VecT& off)       { start -= off; return *this; }

        T Len()   const { return forward.Len(); }
        T LenSq() const { return forward.LenSq(); }

        VecT Lerp(T t) const { return start + forward * t; }
        Tuple<T, T> SolutionsForIntersections(const Line& other) const {
            const float det = forward.x * other.forward.y -
                              forward.y * other.forward.x;
            const float t   = (start.y - other.start.y) * other.forward.x -
                              (start.x - other.start.x) * other.forward.y;
            const float u   = forward.x * (start.y - other.start.y) -
                              forward.y * (start.x - other.start.x);
            if (std::abs(det) < f32s::DELTA)
                return { -1, -1 };
            return { t / det, u / det };
        }

        bool Intersects(const Line& other) const {
            const auto [t, u] = SolutionsForIntersections(other);
            return 0 <= u && u <= 1 && 0 <= t && t <= 1;
        }
        Option<VecT> Intersection(const Line& other) const {
            const auto [t, u] = SolutionsForIntersections(other);
            return 0 <= u && u <= 1 && 0 <= t && t <= 1 ? Options::Some(Lerp(t)) : nullptr;
        }
        bool IntersectsUnclamped(const Line& other) const {
            const float det = forward.x * other.forward.y - forward.y * other.forward.x;
            return std::abs(det) > f32s::DELTA;
        }
        VecT IntersectionUnclamped(const Line& other) const {
            const float det = forward.x * other.forward.y -
                              forward.y * other.forward.x;
            const float t = (start.y - other.start.y) * other.forward.x -
                            (start.x - other.start.x) * other.forward.y;
            return Lerp(t / det);
        }

        T SolutionForNearest(const VecT& p) const {
            return (p - start).Dot(forward) / forward.LenSq();
        }
        VecT NearestTo(const VecT& p) const {
            return Lerp(Math::Clamp(SolutionForNearest(p), 0.0f, 1.0f));
        }

        T DistToSigned(const VecT& p) const {
            return (p - start).Dot(forward.Norm().PerpendLeft());
        }
        T DistTo(const VecT& p) const { return std::abs(DistToSigned(p)); }

        Tuple<T, T> SolutionsForNearestBetween(const Line& other) const {
            const auto [t, u] = SolutionsForIntersections(other);
            const bool tOutBounds = t < 0 || t > 1, uOutBounds = u < 0 || u > 1;
            switch (tOutBounds * 2 + uOutBounds) {
                case 0b00: return { t, u };
                case 0b01:
                    return { SolutionForNearest(u < 0 ? other.start : other.End()), u < 0 ? 0.0f : 1.0f };
                case 0b10:
                    return { t < 0 ? 0.0f : 1.0f, other.SolutionForNearest(t < 0 ? start : End()) };
                case 0b11: {
                    const float uPrime = other.SolutionForNearest(t < 0 ? start : End());
                    if (0 < uPrime && uPrime < 1)
                        return { t < 0 ? 0.0f : 1.0f, uPrime };
                    const float tPrime = SolutionForNearest(u < 0 ? other.start : other.End());
                    return { Clamp(tPrime, 0.0f, 1.0f), u < 0.0f ? 0.0f : 1.0f };
                }
                default: return {};
            }
        }

        Tuple<VecT, VecT> NearestBetween(const Line& other) const {
            const auto [t, u] = SolutionsForNearestBetween(other);
            return { Lerp(t), other.Lerp(u) };
        }

        bool IsOnLeft(const VecT& p) const {
            return forward.Cross(p - start) > 0;
        }
    };

    template <class T = float> using Line2D = Line<Vec2<T>>;
    template <class T = float> using Line3D = Line<Vec3<T>>;
    template <class T = float> using Line4D = Line<Vec4<T>>;
    using fLine2D = Line2D<float>;
    using fLine3D = Line3D<float>;
    using fLine4D = Line4D<float>;
    using dLine2D = Line2D<double>;
    using dLine3D = Line3D<double>;
    using dLine4D = Line4D<double>;

    namespace Lines {
        template <class VecT> static Line<VecT> FromDirection(const VecT& s, const VecT& f) { return { s, f }; }
        template <class VecT> static Line<VecT> FromPoints   (const VecT& s, const VecT& e) { return { s, e - s }; }
    }

    // TODO: ADD MATH METHODS
    template <class VecT>
    union Triangle {
        using T = decltype(VecT {}.x);

        VecT points[3];
        struct Coords {
            T x1, y1, x2, y2, x3, y3;
        } c;

        Triangle(const VecT& a, const VecT& b, const VecT& c) : points { a, b, c } {}
        Line<VecT> LineAt(u32 i) const { return { points[i], points[(i + 1) % 3] }; }

        T DoubledSArea() const { return c.x1 * (c.y2 - c.y3) + c.x2 * (c.y3 - c.y1) + c.x3 * (c.y1 - c.y2); }
        T DoubledArea()  const { return std::abs(DoubledSArea()); }
        T SArea()        const { return DoubledSArea() / 2; }
        T Area()         const { return DoubledArea() / 2; }

        VecT Centroid() const { return (points[0] + points[1] + points[2]) / (T)3; }
        // VecT Incenter()     const;
        // VecT Circumcenter() const;
        // VecT Orthocenter()  const;
        bool IsClockwise() const { return DoubledSArea() > 0; }

        fv3 Barycentric(const VecT& p) const {
            const auto [x, y] = p;
            T det   =  (c.y2 - c.y3) * (c.x1 - c.x3) + (c.x3 - c.x2) * (c.y1 - c.y3);
            T lamb1 = ((c.y2 - c.y3) * (x  - c.x3) + (c.x3 - c.x2) * (y  - c.y3)) / det;
            T lamb2 = ((c.y3 - c.y1) * (x  - c.x3) + (c.x1 - c.x3) * (y  - c.y3)) / det;
            return { lamb1, lamb2, 1 - lamb1 - lamb2 };
        }

        static bool IsValidBary(const fv3& uvw) {
            return uvw.AllGreaterEq(0) && uvw.AllLessEq(1);
        }

        VecT FromBarycentric(const fv3& uvw) const {
            return points[0] * uvw.x + points[1] * uvw.y + points[2] * uvw.z;
        }

        bool Contains(const VecT& p) const { return IsValidBary(Barycentric(p)); }

        template <class V> operator Triangle<V>() const { return { (V)points[0], (V)points[1], (V)points[2] }; }
    };

    template <class T = float> using Triangle2D = Triangle<Vec2<T>>;
    template <class T = float> using Triangle3D = Triangle<Vec3<T>>;
    template <class T = float> using Triangle4D = Triangle<Vec4<T>>;
    using fTriangle2D = Triangle2D<float>;
    using fTriangle3D = Triangle3D<float>;
    using fTriangle4D = Triangle4D<float>;
    using dTriangle2D = Triangle2D<double>;
    using dTriangle3D = Triangle3D<double>;
    using dTriangle4D = Triangle4D<double>;
}
