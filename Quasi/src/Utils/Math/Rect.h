#pragma once

#include "Vector.h"

namespace Quasi::Math {
    enum class Dir {
        MIDDLE = 0,
        CENTER = 0,
        RIGHT = 1,
        LEFT  = 2,
        TOP,
        BOTTOM,
        FRONT,
        BACK,
        IN,
        OUT,
    };

    template <class T, usize N> struct Rect {
        using fT     = Common<T, f32>;
        using VecT   = Vector<T, N>;
        using RangeT = Range<T>;
        VecT min, max;

        Rect() : min(0), max(0) {}
        Rect(const RangeT (&bounds)[N]) {
            for (usize i = 0; i < N; ++i) {
                min[i] = bounds[i].min;
                max[i] = bounds[i].max;
            }
        }
        Rect(const VecT& min, const VecT& max) : min(min), max(max) {}
        Rect(const RangeT (&bounds)[N], CheckedMarker) {
            for (usize i = 0; i < N; ++i) {
                min[i] = bounds[i].RecheckedMin();
                max[i] = bounds[i].RecheckedMax();
            }
        }
        Rect(const VecT& min, const VecT& max, CheckedMarker) : min(VecT::Min(min, max)), max(VecT::Min(min, max)) {}
        Rect(const VecT& min, const VecT& max, InclusiveMarker) requires Integer<T>  : min(min), max(max + 1) {}
        Rect(const VecT& min, const VecT& max, InclusiveMarker) requires Floating<T> : min(min), max(max) {}

        static Rect FromSize  (const VecT& min,    const VecT& size) { return { min, min + size }; }
        static Rect FromCenter(const VecT& center, const VecT& size) { return { center - size * 0.5f, center + size * 0.5f, Inclusive }; }
        static Rect Empty()      { return {}; }
        static Rect FullDomain() { return { NumInfo<T>::MIN, NumInfo<T>::MAX }; }
        static Rect AntiDomain() { return { NumInfo<T>::MIN, NumInfo<T>::MAX }; }
        static Rect On(const VecT& point) { return { point, point, Inclusive }; }
        static Rect Over(const Collection<VecT> auto& nums) {
            Rect r = AntiDomain();
            for (const auto& v : nums) r.ExpandToFit(v);
            return r;
        }

        VecT Size()   const { return max - min; }
        VecT Center() const { return (max + min) / 2; }
        VecT RecheckedMin() const { return VecT::Min(min, max); }
        VecT RecheckedMax() const { return VecT::Max(min, max); }

        RangeT RangeX() const requires (N >= 1) { return { min.x, max.x }; }
        RangeT RangeY() const requires (N >= 2) { return { min.y, max.y }; }
        RangeT RangeZ() const requires (N >= 3) { return { min.z, max.z }; }
        RangeT RangeW() const requires (N >= 4) { return { min.w, max.w }; }
        RangeT RangeN(usize n) const { return { min[n], max[n] }; }
        RangeT operator[](usize n) const { return RangeN(n); }

        VecT TopRight()    const requires (N == 2) { return max; }
        VecT TopLeft()     const requires (N == 2) { return { min.x, max.y }; }
        VecT BottomRight() const requires (N == 2) { return { max.x, min.y }; }
        VecT BottomLeft()  const requires (N == 2) { return min; }

        template <usize M>
        Rect<T, M> SwizzleRect(const char (&swizzle)[M + 1]) const {
            Rect<T, M> swizzled;
            for (usize i = 0; i < M; ++i) {
                const usize comp = VecT::CompFromName(swizzle[i]);
                if (comp == -1) continue;
                swizzled.min[i] = min[i];
                swizzled.max[i] = max[i];
            }
            return swizzled;
        }
        template <usize M> Rect<T, M> operator[](const char (&swizzle)[M + 1]) { return SwizzleRect(swizzle); }

        T Width()    const                   { return max[0] - min[0]; }
        T Height()   const requires (N >= 2) { return max[1] - min[1]; }
        T Depth()    const requires (N >= 3) { return max[2] - min[2]; }
        T Duration() const requires (N >= 4) { return max[3] - min[3]; }
        T LengthX()  const                   { return max[0] - min[0]; }
        T LengthY()  const requires (N >= 2) { return max[1] - min[1]; }
        T LengthZ()  const requires (N >= 3) { return max[2] - min[2]; }
        T LengthW()  const requires (N >= 4) { return max[3] - min[3]; }
        T LengthN(usize n) const { return max[n] - min[n]; }

        Rect<T, N + 1> AddZ(const RangeT& z) const requires (N == 2) { return { min.AddZ(z.min), max.AddZ(z.max) }; }
        Rect<T, N + 1> AddW(const RangeT& w) const requires (N == 3) { return { min.AddW(w.min), max.AddW(w.max) }; }

        T Volume() const {
            T volume = Width();
            for (usize i = 1; i < N; ++i) volume *= (max[N] - min[N]);
            return volume;
        }
        T Area() const requires (N == 2) { return Volume(); }

        VecT Corner(const bool (&rel)[N]) const { // each bool is a y/n decision on min or max (0 = min, 1 is max)
            VecT result;
            for (usize i = 0; i < N; ++i) result[i] = rel[i] ? max[i] : min[i];
            return result;
        }
        VecT Corner(const Dir (&rel)[N]) const {
            VecT result;
            for (usize i = 0; i < N; ++i) result[i] = ((int)rel[i] & 1) ? max[i] : min[i];
            return result;
        }
        VecT Anchor(const int (&rel)[N]) const { // each int is a ternary decision on min (-1), center (0) or max (1)
            VecT result;
            for (usize i = 0; i < N; ++i)
                result[i] = rel[i] == -1 ? min[i] :
                            rel[i] == 0 ? (min[i] + max[i]) / 2 :
                            max[i];
            return result;
        }
        VecT Anchor(const Dir (&rel)[N]) const {
            VecT result;
            for (usize i = 0; i < N; ++i)
                result[i] = ((int)rel[i] & 1) ? min[i] :
                            (rel[i] == Dir::MIDDLE) ? (min[i] + max[i]) / 2 :
                            max[i];
            return result;
        }
        VecT Relative(const Vector<fT, N>& rel) const {
            VecT result;
            for (usize i = 0; i < N; ++i)
                result[i] = std::lerp(min[i], max[i], rel[i]);
            return result;
        }
        VecT Unmap(const VecT& x) { return (x - min) / (max - min); }

        Rect Move(const VecT& offset) const { return { min + offset, max + offset }; }
        Rect RelativeTo(const VecT& offset) const { return { min - offset, max - offset }; }
        Rect RelativeTo(const Rect& other) const {
            const VecT m = (T)1 / other.Size();
            return { (min - other.min) * m, (max - other.max) * m };
        }
        Rect Scale(T scale)  const { return { min * scale, max * scale }; }
        Rect Scale(fT scale) const requires Integer<T> { return { (VecT)(min * scale), (VecT)(max * scale) }; }
        Rect ScaleCentered(T scale) const { const VecT off = Size() * (scale - 1); return { min - off, max + off }; }
        Rect ScaleAnchored(T scale, const VecT& anchor) const {
            const VecT toMin = (min - anchor) * (scale - 1), toMax = (max - anchor) * (scale - 1);
            return { min + toMin, max + toMax };
        }
        Rect Scale(const VecT& scale) const { return { min * scale, max * scale }; }
        Rect ScaleCentered(const VecT& scale) const { const VecT off = Size() * (scale - 1); return { min - off, max + off }; }
        Rect ScaleAnchored(const VecT& scale, const VecT& anchor) const {
            const VecT toMin = (min - anchor) * (scale - 1), toMax = (max - anchor) * (scale - 1);
            return { min + toMin, max + toMax };
        }

        Rect operator+(const VecT& offset)   const { return Move(offset); }
        Rect operator-(const VecT& offset)   const { return { min - offset, max - offset }; }
        Rect operator*(T scale)              const { return Scale(scale); }
        Rect operator/(T invScale)           const { return { min / invScale, max / invScale }; }
        Rect operator*(const VecT& scale)    const { return { min * scale, max * scale }; }
        Rect operator/(const VecT& invScale) const { return { min / invScale, max / invScale }; }

        template <class U>
        Rect<U, N> As() const { return { min.template As<U>(), max.template As<U>() }; }
        template <class U>
        explicit operator Rect<U, N>() const { return As<U>(); }

        VecT Clamp(const VecT& val) const { return val.Clamp(min, max); }

        Rect Fixed() const { return { VecT::Min(min, max), VecT::Max(min, max) }; }
        
        bool Contains(const Rect& other) const requires Integer<T>  { return min.AllLessEq(other.min) && other.max.AllLess(max); }
        bool Contains(const VecT& other) const requires Integer<T>  { return min.AllLessEq(other)     && other.AllLess(max); }
        bool Contains(const Rect& other) const requires Floating<T> { return min.AllLessEq(other.min) && other.max.AllLessEq(max); }
        bool Contains(const VecT& other) const requires Floating<T> { return min.AllLessEq(other)     && other.AllLessEq(max); }

        void ExpandToFit(const VecT& newPoint) {
            min = VecT::Min(min, newPoint); max = VecT::Max(max, newPoint);
        }
        Rect Union(const Rect& other)     const { return { VecT::Min(min, other.min), VecT::Max(max, other.max) }; }
        Rect Expand(const VecT& other)    const { return { VecT::Min(min, other),     VecT::Max(max, other)     }; }
        Rect intersect(const Rect& other) const { return { VecT::Max(min, other.min), VecT::Min(max, other.max) }; }

        Rect Inset  (T radius)           const { return { min + radius, max - radius }; }
        Rect Inset  (const VecT& radius) const { return { min + radius, max - radius }; }
        Rect Extrude(T radius)           const { return { min - radius, max + radius }; }
        Rect Extrude(const VecT& radius) const { return { min - radius, max + radius }; }

        bool Overlaps(const Rect& other) const requires Integer<T>  { return min.AllLess(other.max) && max.AllGreater(other.min); }
        bool Overlaps(const Rect& other) const requires Floating<T> { return min.AllLessEq(other.max) && max.AllGreaterEq(other.min); }
        VecT OverlappingSize(const Rect& other) const { return VecT::Max(max - other.min, other.max - min); }
    };
    template <class T, usize N>
    Vector<T, N> IVector<T, N>::Clamp(const Rect<T, N>& rect) const {
        return Clamp(rect.min, rect.max);
    }

    template <class T, usize N>
    bool IVector<T, N>::IsIn(const Rect<T, N>& rect) const { return rect.Contains(super()); }

    template <class T, usize N>
    Vector<T, N> IVector<T, N>::MapCoords(const Rect<T, N>& source, const Rect<T, N>& dest) const {
        return dest.min + (dest.Size() / source.Size()) * (super() - source.min);
    }
    template <class T, usize N>
    Vector<T, N> IVector<T, N>::MapFromUnit(const Rect<T, N>& dest) const {
        return dest.Relative(super());
    }
    template <class T, usize N>
    Vector<T, N> IVector<T, N>::UnmapToUnit(const Rect<T, N>& source) const {
        return (super() - source.min) / (source.max - source.min);
    }

    template <class T> using Rect2D = Rect<T, 2>;
    template <class T> using Rect3D = Rect<T, 3>;
    template <class T> using Rect4D = Rect<T, 4>;
    using fRect2D = Rect2D<float>;
    using fRect3D = Rect3D<float>;
    using fRect4D = Rect4D<float>;
    using dRect2D = Rect2D<double>;
    using dRect3D = Rect3D<double>;
    using dRect4D = Rect4D<double>;
    using iRect2D = Rect2D<int>;
    using iRect3D = Rect3D<int>;
    using iRect4D = Rect4D<int>;
    using uRect2D = Rect2D<uint>;
    using uRect3D = Rect3D<uint>;
    using uRect4D = Rect4D<uint>;
    using bRect2D = Rect2D<byte>;
    using bRect3D = Rect3D<byte>;
    using bRect4D = Rect4D<byte>;
}
