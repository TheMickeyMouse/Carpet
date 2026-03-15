#pragma once
#include "Type.h"

namespace Quasi {
    enum InclusiveMarker { Inclusive };

    template <class T> struct Range {
        using fT = Common<T, f32>;

        T min, max;
        Range() : min(0), max(0) {}
        Range(T max) : min(0), max(max) {}
        Range(T min, T max) : min(min), max(max) {}
        Range(T max, InclusiveMarker)        requires Integer<T>  : min(0),   max(max + 1) {}
        Range(T min, T max, InclusiveMarker) requires Integer<T>  : min(min), max(max + 1) {}
        Range(T max, InclusiveMarker)        requires Floating<T> : min(0),   max(max + 1) {}
        Range(T min, T max, InclusiveMarker) requires Floating<T> : min(min), max(max + 1) {}

        static Range FromSize  (T min,    T size) { return { min, min + size }; }
        static Range FromCenter(T center, T size) { return { center - size, center + size, Inclusive }; }
        static Range Empty()      { return {}; }
        static Range FullDomain() { return { NumInfo<T>::MIN, NumInfo<T>::MAX }; }
        static Range AntiDomain() { return { NumInfo<T>::MAX, NumInfo<T>::MIN }; }
        static Range On(T point) { return { point, point, Inclusive }; }
        template <class R> static Range Over(const R& nums) {
            Range r = AntiDomain();
            for (const auto& v : nums) r.ExpandToFit(v);
            return r;
        }

        T Size()   const { return max - min; }
        T Length() const { return max - min; }
        T RecheckedMin() const { return std::min(min, max); }
        T RecheckedMax() const { return std::max(min, max); }
        T Center() const { return (max + min) / 2; }
        bool IsEmpty() const { return min == max; }

        T MapTo(T x, const Range& newRange) const { return ((x - min) * newRange.Length() / Length()) + newRange.min; }
        T Map  (T x) const { return std::lerp(min, max, x); }
        T Unmap(T x) const { return (x - min) / (max - min); }
        T Lerp (T x) const { return Map(x); }

        Range Move(T offset)      const { return { min + offset, max + offset }; }
        Range RelativeTo(T x)     const { return { min - x, max - x }; }
        Range RelativeTo(const Range& x) const {
            const T m = (T)1 / x.Length();
            return { (min - x.min) * m, (max - x.max) * m };
        }
        Range Scale(T scale)  const { return { min * scale, max * scale }; }
        Range Scale(fT scale) const requires Integer<T> { return { (T)(min * scale), (T)(max * scale) }; }
        Range ScaleCentered(T scale) const { const T off = Size() * (scale - 1); return { min - off, max + off }; }
        Range ScaleAnchored(T scale, T anchor) const {
            const T toMin = (min - anchor) * (scale - 1), toMax = (max - anchor) * (scale - 1);
            return { min + toMin, max + toMax };
        }

        Range operator+(T offset) const { return Move(offset); }
        Range operator-(T offset) const { return { min - offset, max - offset }; }
        Range operator*(T scale) const { return Scale(scale); }
        Range operator/(T invScale) const { return { min / invScale, max / invScale }; }

        T Clamp(T val) const { return Math::Clamp(val, min, max); }
        Range Clip(const Range& other) const { return { Clamp(other.min), Clamp(other.max) }; }

        Range Fixed() const { return { std::min(min, max), std::max(min, max) }; }

        bool Contains(const Range& other) const requires Integer<T>  { return min <= other.min && other.max <  max; }
        bool Contains(T other)            const requires Integer<T>  { return min <= other     && other     <  max; }
        bool Contains(const Range& other) const requires Floating<T> { return min <= other.min && other.max <= max; }
        bool Contains(T other)            const requires Floating<T> { return min <= other     && other     <= max; }

        void ExpandToFit(T newPoint) requires Floating<T> {
            min = std::min(min, newPoint); max = std::max(max, newPoint);
        }
        void ExpandToFit(T newPoint) requires Integer<T> {
            min = std::min(min, newPoint); max = std::max(max, newPoint + 1);
        }
        Range Union(const Range& other)     const { return { std::min(min, other.min), std::max(max, other.max) }; }
        Range ExpandTo(T other)             const { return { std::min(min, other),     std::max(max, other)     }; }
        Range Intersect(const Range& other) const { return { std::max(min, other.min), std::min(max, other.max) }; }

        Range Inset  (T radius) const { return { min + radius, max - radius }; }
        Range Extrude(T radius) const { return { min - radius, max + radius }; }

        bool Overlaps       (const Range& other) const requires Integer<T>  { return min <  other.max && other.min <  max; }
        bool Overlaps       (const Range& other) const requires Floating<T> { return min <= other.max && other.min <= max; }
        T    OverlappingSize(const Range& other) const { return std::max(max - other.min, other.max - min); }

        // support iteration
        T begin()  const { return min; }
        T cbegin() const { return min; }
        T end()  const { return max; }
        T cend() const { return max; }
    };

    using iRange = Range<int>;
    using uRange = Range<uint>;
    using zRange = Range<usize>;
    using fRange = Range<float>;
    using dRange = Range<double>;
}
