#pragma once
#include <cmath>

#include "Angles.h"
#include "Utils/Text/Num.h"

#include "Utils/Array.h"
#include "Utils/Iter/SplitIter.h"
#include "Utils/Iter/EnumerateIter.h"

namespace Quasi::Math {
    struct Rotor2D;
    struct RandomGenerator;
    struct Transform2D;

    template <class T, usize N> struct Vector;
    using iv2 = Vector<int,    2>;
    using iv3 = Vector<int,    3>;
    using iv4 = Vector<int,    4>;
    using uv2 = Vector<uint,   2>;
    using uv3 = Vector<uint,   3>;
    using uv4 = Vector<uint,   4>;
    using fv2 = Vector<float,  2>;
    using fv3 = Vector<float,  3>;
    using fv4 = Vector<float,  4>;
    using dv2 = Vector<double, 2>;
    using dv3 = Vector<double, 3>;
    using dv4 = Vector<double, 4>;
    using bv2 = Vector<byte,   2>;
    using bv3 = Vector<byte,   3>;
    using bv4 = Vector<byte,   4>;
    template <class T> using Unit = Vector<T, 1>;
    template <class T> using Vec2 = Vector<T, 2>;
    template <class T> using Vec3 = Vector<T, 3>;
    template <class T> using Vec4 = Vector<T, 4>;

    template <class T, usize N> struct Rect;

    template <class T, usize N> struct IVector {
        using Super = Vector<T, N>;
        using Elm = T;
        enum { Dim = N };
        using fT = Common<T, f32>;
    private:
        const Super& super() const { return *static_cast<const Super*>(this); }
        Super& super() { return *static_cast<Super*>(this); }
    protected:
        T*       DataImpl() = delete;
        const T* DataImpl() const = delete;
        static usize CompFromNameImpl(char c) = delete;
    public:
        static usize CompFromName(char c)  { return Super::CompFromNameImpl(c); }
        T*       Data()          { return super().DataImpl(); }
        const T* Data() const    { return super().DataImpl(); }
        T*       DataEnd()       { return super().DataImpl() + N; }
        const T* DataEnd() const { return super().DataImpl() + N; }
        Span<const T> AsSpan() const { return Spans::Slice(Data(), N); }
        Span<T>       AsSpan()       { return Spans::Slice(Data(), N); }

        T&       At(usize i)       { return Data()[i]; }
        const T& At(usize i) const { return Data()[i]; }
        T&       operator[](usize i)       { return Data()[i]; }
        const T& operator[](usize i) const { return Data()[i]; }

        template <usize M>
        Vector<T, M> Swizzle(const char (&swizzle)[M + 1]) const {
            Vector<T, M> swizzled;
            for (usize i = 0; i < M; ++i) {
                const usize comp = CompFromName(swizzle[i]);
                swizzled[i] = comp == -1 ? 0 : At(comp);
            }
            return swizzled;
        }
        template <usize M> Vector<T, M> operator[](const char (&swizzle)[M + 1]) { return Swizzle(swizzle); }

        usize Dimensions() const { return N; }

        static Super FromSpan(Span<const T> elms) {
            Super v;
            Memory::RangeCopy(v.Data(), elms.Data(), std::min(elms.Length(), N));
            return v;
        }
        // static Super FromAxis(some axis type, T scale);
        static Super FromCorner(const bool (&rel) [N], T scale = 1) {
            Super v;
            for (usize i = 0; i < N; ++i) v[i] = rel[i] ? scale : -scale;
            return v;
        }
        static Super FromScale(T scale) {
            Super v;
            Memory::RangeSet(v.Data(), scale, N);
            return v;
        }
        static Super Zero() { return {}; }
        static Super One() { return FromScale(1); }

        Vector<T, N + 1> AddComponent(T extra) const {
            Vector<T, N + 1> v;
            Memory::RangeCopy(v.Data(), Data(), N);
            v[N] = extra;
            return v;
        }
        Vector<T, N - 1> RemoveComponent() const {
            Vector<T, N - 1> v;
            Memory::RangeCopy(v.Data(), Data(), N - 1);
            return v;
        }

        template <class U, usize M = N> Vector<U, M> As() const {
            Vector<U, M> v;
            static constexpr usize CopyLen = std::min(N, M);
            for (usize i = 0; i < CopyLen; ++i) v[i] = (U)At(i);
            return v;
        }

        template <class U, usize M> explicit operator Vector<U, M>() const { return As<U, M>(); }

        bool IsZero() const { return All([] (T x) { return x == 0; }); }
        bool NearZero() const { return LenSq() < (T)(f32s::DELTA * f32s::DELTA); }
        Comparison Cmp(const Super& other) const { return AsSpan().Cmp(other.AsSpan()); }

        Super Neg() const { return Map(Operators::UNeg {}); }
        Super Add(const Super& other) const           { return BinaryMap(other, Operators::Add {}); }
        Super Sub(const Super& other) const           { return BinaryMap(other, Operators::Sub {}); }
        Super Mul(T scale) const                      { return Map(scale, Operators::Mul {}); }
        Super Div(T scale) const requires Integer<T>  { return Map(scale, Operators::Div {}); }
        Super Div(T scale) const requires Floating<T> { return Mul((T)1 / scale); }
        Super AddScalar(T off) const                  { return Map(off, Operators::Add {}); }
        Super SubScalar(T off) const                  { return Map(off, Operators::Sub {}); }
        Super MulComps(const Super& other) const      { return BinaryMap(other, Operators::Mul {}); }
        Super DivComps(const Super& other) const      { return BinaryMap(other, Operators::Div {}); }
        Super Mod(T m) const { return Map([=] (T x)   { return NumInfo<T>::Modulo(x, m); }); }
        Super ModComps(const Super& other) const      { return BinaryMap(other, Operators::NumericModulo {}); }

        Super& AddAssign(const Super& other)          { return BinaryAssign(other, Operators::AddAssign {}); }
        Super& SubAssign(const Super& other)          { return BinaryAssign(other, Operators::SubAssign {}); }
        Super& MulAssign(T scale)                     { return MapAssign(scale, Operators::MulAssign {}); }
        Super& DivAssign(T scale) requires Integer<T> { return MapAssign(scale, Operators::DivAssign {}); }
        Super& DivAssign(T scale) requires Floating<T> { return MulAssign((T)1 / scale); }
        Super& AddScalarAssign(T off)                 { return MapAssign(off, Operators::AddAssign {}); }
        Super& SubScalarAssign(T off)                 { return MapAssign(off, Operators::SubAssign {}); }
        Super& MulCompsAssign(const Super& other)     { return BinaryAssign(other, Operators::MulAssign {}); }
        Super& DivCompsAssign(const Super& other)     { return BinaryAssign(other, Operators::DivAssign {}); }

        Super operator+() const { return *this; }
        Super operator-() const { return Neg(); }

        Super operator+(const Super& other) const { return Add(other); }
        Super operator+(T off)              const { return AddScalar(off); }
        Super operator-(const Super& other) const { return Sub(other); }
        Super operator-(T off)              const { return SubScalar(off); }
        Super operator*(const Super& other) const { return MulComps(other); }
        Super operator*(T scale)            const { return Mul(scale); }
        Super operator/(const Super& other) const { return DivComps(other); }
        Super operator/(T scale)            const { return Div(scale); }
        Super operator%(const Super& other) const { return ModComps(other); }
        Super operator%(T m)                const { return Mod(m); }

        Super& operator+=(const Super& other) { return AddAssign(other); }
        Super& operator+=(T off)              { return AddScalarAssign(off); }
        Super& operator-=(const Super& other) { return SubAssign(other); }
        Super& operator-=(T off)              { return SubScalarAssign(off); }
        Super& operator*=(const Super& other) { return MulCompsAssign(other); }
        Super& operator*=(T scale)            { return MulAssign(scale); }
        Super& operator/=(const Super& other) { return DivCompsAssign(other); }
        Super& operator/=(T scale)            { return DivAssign(scale); }
        Super& operator%=(const Super& other) { return super() = ModComps(other); }
        Super& operator%=(T m)                { return super() = Mod(m); }

        auto Map(const FnArgs<T> auto& mapping) const {
            Vector<FuncResult<decltype(mapping), T>, N> v;
            for (usize i = 0; i < N; ++i) { v[i] = mapping(At(i)); }
            return v;
        }
        auto Map(T other, const FnArgs<T, T> auto& mapping) const {
            Vector<FuncResult<decltype(mapping), T, T>, N> v;
            for (usize i = 0; i < N; ++i) { v[i] = mapping(At(i), other); }
            return v;
        }
        auto BinaryMap(const Super& other, const FnArgs<T, T> auto& mapping) const {
            Vector<FuncResult<decltype(mapping), T, T>, N> v;
            for (usize i = 0; i < N; ++i) { v[i] = mapping(At(i), other[i]); }
            return v;
        }
        Super& MapAssign(T other, const FnArgs<T&, T> auto& mapping) {
            for (usize i = 0; i < N; ++i) mapping(At(i), other);
            return super();
        }
        Super& BinaryAssign(const Super& other, const FnArgs<T&, T> auto& mapping) {
            for (usize i = 0; i < N; ++i) mapping(At(i), other[i]);
            return super();
        }

        fT Len  () const { return std::sqrt((fT)LenSq()); }
        T  LenSq() const { return Dot(super()); }
        fT Dist  (const Super& to) const { return (super() - to).Len(); }
        T  DistSq(const Super& to) const { return (super() - to).LenSq(); }
        bool InRange(const Super& other, T d) const { return DistSq(other) <= d * d; }
        Super Norm()        const requires Floating<T> { return Div(Len()); }
        Super Norm(float d) const requires Floating<T> { return Norm() * d; }
        Tuple<Super, fT> NormAndLen() const requires Floating<T> { const fT len = Len(); return { Div(len), len }; }
        Super Tangent(const Super& other)          const requires Floating<T> { return (other - super()).Norm(); }
        Super Tangent(const Super& other, float d) const requires Floating<T> { return (other - super()).Norm(d); }
        Super Normal(const Super& other)           const requires Floating<T> { return (other - super()).Norm().Perpend(); }
        Tuple<Super, fT> DirAndLen(const Super& other) const requires Floating<T> { const fT len = (other - super()).NormAndLen(); return { Div(len), len }; }
        Super SafeNorm()    const requires Floating<T> { return NearZero() ? 0 : Norm(); }

        T Dot(const Super& other) const {
            T sum = At(0) * other[0];
            for (usize i = 1; i < N; ++i) sum += At(i) * other[i];
            return sum;
        }
        Super Project(const Super& axis) const { return axis.Mul(Dot(axis) / axis.LenSq()); }
        Super Reflect(const Super& normal) const { return Sub((2 * Dot(normal)) * normal); }

        Vector<fT, N> Lerp(const Super& other, fT t) const { return BinaryMap(other, [t = t, u = 1 - t] (T a, T b) { return u * a + t * b; }); }
        Super& LerpToward(const Super& other, T t) requires Floating<T> { return BinaryAssign(other, [=] (T& a, T b) { a += (b - a) * t; }); }
        Super& StepToward(const Super& other, T d) requires Floating<T> { const auto [dir, s] = (other - super()).NormAndLen(); return AddAssign(dir * std::min(s, d)); }
        Super& StepExact (const Super& other, T d) requires Floating<T> { const auto [dir, s] = (other - super()).NormAndLen(); return AddAssign(dir * d); }
        Super Slerp(const Super& other, fT t) const requires Floating<T> {
            const Radians theta = AngleBetween(other);
            const fT inv = 1 / Sin(theta);
            return BinaryMap(other, [p = Trig::Sin(theta * (1 - t)) * inv, q = Trig::Sin(theta * t) * inv] (T a, T b) {
                return a * p + b * q;
            });
        }

        Radians AngleBetween(const Super& other) const { return Trig::Arccos(Dot(other) / (Len() * other.Len())); }

        Super Clamp() const requires Floating<T> { return Clamp(0, 0); }
        Super Clamp(T min, T max) const { return Map([&] (T x) { return Math::Clamp(x, min, max); }); }
        Super Clamp(const Super& min, const Super& max) const {
            Super v;
            for (usize i = 0; i < N; ++i) v[i] = Math::Clamp(At(i), min[i], max[i]);
            return v;
        }
        Super Clamp(const Rect<T, N>& rect) const;
        Super MapCoords(const Rect<T, N>& source, const Rect<T, N>& dest) const;
        Super MapFromUnit(const Rect<T, N>& dest) const;
        Super UnmapToUnit(const Rect<T, N>& source) const;

        Super ClampLen(T d) const requires Floating<T> {
            const auto [dir, s] = NormAndLen();
            return dir * std::max(s, d);
        }

        static Super Max(const Super& x, const Super& y) { return x.BinaryMap(y, [] (T a, T b) { return std::max(a, b); }); }
        static Super Min(const Super& x, const Super& y) { return x.BinaryMap(y, [] (T a, T b) { return std::min(a, b); }); }
        static Super MaxOver(const Collection<Super> auto& xs) {
            Super max = { NumInfo<T>::MIN };
            for (const auto& x : xs) max = Max(max, x);
            return max;
        }
        static Super MinOver(const Collection<Super> auto& xs) {
            Super min = { NumInfo<T>::MAX };
            for (const auto& x : xs) min = Min(min, x);
            return min;
        }

        bool operator==(const IVector&) const = default;
        bool AllGreater(const Super& other) const {
            for (usize i = 0; i < N; ++i) if (At(i) <= other[i]) return false;
            return true;
        }
        bool AllLess(const Super& other) const {
            for (usize i = 0; i < N; ++i) if (At(i) >= other[i]) return false;
            return true;
        }
        bool AllGreaterEq(const Super& other) const {
            for (usize i = 0; i < N; ++i) if (At(i) < other[i]) return false;
            return true;
        }
        bool AllLessEq(const Super& other) const {
            for (usize i = 0; i < N; ++i) if (At(i) > other[i]) return false;
            return true;
        }
        bool IsIn(const Super& min, const Super& max) const { return ALlGreater(min) && AllLess(max); }
        bool IsIn(const Rect<T, N>& rect) const;

        static Super Random(RandomGenerator& rand);
        static Super Random(RandomGenerator& rand, const Super& min, const Super& max);
        static Super Random(RandomGenerator& rand, const Rect<T, N>& range);
        static Super RandomOnUnit(RandomGenerator& rand) requires Floating<T>;
        static Super RandomInUnit(RandomGenerator& rand) requires Floating<T>;

        static Option<Super> Parse(Str s, Str sep) { return Parse(s, sep, [] (Str x) { return Text::Parse<T>(x); }); }
        static Option<Super> Parse(Str s, Str sep, Fn<Option<T>, Str> auto&& parserForElms) {
            Super v;
            for (const auto [i, e] : s.Split(sep).Enumerate()) {
                if (i >= N) return nullptr;
                Option<T> elm = parserForElms(e);
                if (!elm) return nullptr;
                v[i] = *elm;
            }
            return v;
        }
    };

    template <class T, usize N> Vector<T, N> operator+(NoInfer<T> val, const Vector<T, N>& vec) { return vec + val; }
    template <class T, usize N> Vector<T, N> operator-(NoInfer<T> val, const Vector<T, N>& vec) { return vec.Map(val, [] (T x, T v) { return (T)(v - x); }); }
    template <class T, usize N> Vector<T, N> operator*(NoInfer<T> val, const Vector<T, N>& vec) { return vec * val; }
    template <class T, usize N> Vector<T, N> operator/(NoInfer<T> val, const Vector<T, N>& vec) { return vec.Map(val, [] (T x, T v) { return (T)(v / x); }); }

    template <class T, usize N> struct Vector : IVector<T, N> {
        Array<T, N> elems;
    protected:
        T* DataImpl() { return elems.Data(); }
        const T* DataImpl() const { return elems.Data(); }
        static usize CompFromNameImpl(char c) { return c == '\0' ? -1ULL : (usize)(c - 1); }
    public:
        Vector(T base = 0) { elems.Fill(base); }
        Vector(const Array<T, N>& array) : elems(array) {}

        bool operator==(const Vector&) const = default;
    };

    template <class T> struct Vector<T, 1> : IVector<T, 1> {
        friend IVector<T, 1>;
        T x;
    protected:
        T* DataImpl() { return &x; }
        const T* DataImpl() const { return &x; }
        static usize CompFromNameImpl(char c) {
            switch (c) {
                case 'x': case 's': case 'r': return 0;
                default: return -1;
            }
        }
    public:
        Vector(T x = 0) : x(x) {}

        operator const T&() const { return x; }
        operator T&() { return x; }
        bool operator==(const Vector&) const = default;
        bool operator> (T y) const { return x >  y; }
        bool operator>=(T y) const { return x >= y; }
        bool operator<=(T y) const { return x <= y; }
        bool operator< (T y) const { return x <  y; }
        T& operator++()    { return ++x; }
        T  operator++(int) { return x++; }
    };

    template <Numeric T> struct Vector<T, 2> : IVector<T, 2> {
        friend IVector<T, 2>;
        using fT = typename IVector<T, 2>::fT;
        T x, y;
    protected:
        T* DataImpl() { return &x; }
        const T* DataImpl() const { return &x; }
        static usize CompFromNameImpl(char c) {
            switch (c) {
                case 'x': case 's': case 'r': return 0;
                case 'y': case 't': case 'g': return 1;
                default: return -1;
            }
        }
    public:
        Vector(T s = 0) : x(s), y(s) {}
        Vector(T x, T y) : x(x), y(y) {}

        static Vector XAxis() { return { 1, 0 }; }
        static Vector YAxis() { return { 0, 1 }; }
        static Vector XPos()                    { return { +1,  0 }; } static Vector Right()                   { return XPos(); }
        static Vector XNeg() requires Signed<T> { return { -1,  0 }; } static Vector Left() requires Signed<T> { return XNeg(); }
        static Vector YPos()                    { return {  0, +1 }; } static Vector Up()                      { return YPos(); }
        static Vector YNeg() requires Signed<T> { return {  0, -1 }; } static Vector Down() requires Signed<T> { return YNeg(); }

        T Cross(const Vector& other) const { return x * other.y - y * other.x; }

        Vector FlipX()    const { return { -x, y }; }
        Vector FlipY()    const { return { x, -y }; }
        Vector Conj()    const { return { x, -y }; }
        fT Slope()       const { return (fT)y / (fT)x; }
        fT AspectRatio() const { return (fT)x / (fT)y; }

        Radians PolarAngle() const { return Trig::Atan2(y, x); }
        Radians SignedAngleBetween(const Vector& other) const { return Trig::Atan2(Cross(other), this->Dot(other)); }

        Tuple<fT, Radians> PolarCoords() const { return { this->Len(), this->PolarAngle() }; }
        static Vector FromPolar(T r, Radians theta) requires Floating<T> { return { r * Cos(theta), r * Sin(theta) }; }
        static Vector FromPolar(T r, const Rotor2D& theta) requires Floating<T>;

        Vector Perpend()          const { return { -y, x }; }
        Vector Perpend(bool left) const { return { left ? -y : y, left ? x : -x }; }
        Vector PerpendLeft()      const { return { -y, x }; }
        Vector PerpendRight()     const { return { y, -x }; }

        Vector RotateBy(const Rotor2D& r) const;
        Vector TransformBy(const Transform2D& t) const;

        Vector ComplexMul(const Vector& v) const {
            return { x * v.x - y * v.y, x * v.y + y * v.x };
        }
        Vector ComplexMul(T re, T im) const {
            return { x * re - y * im, x * im + y * re };
        }
        Vector GeometricMul(const Vector& v) const {
            return { x * v.x + y * v.y, x * v.y - y * v.x };
        }
        Vector GeometricMul(T re, T im) const {
            return { x * re + y * im, x * im - y * re };
        }

        Vec3<T> AddZ(T z) const { return { x, y, z }; }

        bool operator==(const Vector&) const = default;
    };

    template <class T> struct Vector<T, 2> { T x, y; };

    template <Numeric T> struct Vector<T, 3> : IVector<T, 3> {
        friend IVector<T, 3>;
        using fT = typename IVector<T, 2>::fT;
        T x, y, z;
    protected:
        T* DataImpl() { return &x; }
        const T* DataImpl() const { return &x; }
        static usize CompFromNameImpl(char c) {
            switch (c) {
                case 'x': case 's': case 'r': return 0;
                case 'y': case 't': case 'g': return 1;
                case 'z': case 'u': case 'b': return 2;
                default: return -1;
            }
        }
    public:
        Vector(T s = 0) : x(s), y(s), z(s) {}
        Vector(T x, T y, T z) : x(x), y(y), z(z) {}

        static Vector XAxis() { return { 1, 0, 0 }; }
        static Vector YAxis() { return { 0, 1, 0 }; }
        static Vector ZAxis() { return { 0, 0, 1 }; }
        static Vector XPos()                    { return { +1,  0,  0 }; } static Vector Right()                   { return XPos(); }
        static Vector XNeg() requires Signed<T> { return { -1,  0,  0 }; } static Vector Left() requires Signed<T> { return XNeg(); }
        static Vector YPos()                    { return {  0, +1,  0 }; } static Vector Up()                      { return YPos(); }
        static Vector YNeg() requires Signed<T> { return {  0, -1,  0 }; } static Vector Down() requires Signed<T> { return YNeg(); }
        static Vector ZPos()                    { return {  0,  0, +1 }; } static Vector Front()                   { return ZPos(); }
        static Vector ZNeg() requires Signed<T> { return {  0,  0, -1 }; } static Vector Back() requires Signed<T> { return ZNeg(); }

        Vector FlipX() const { return { -x, y, z }; }
        Vector FlipY() const { return { x, -y, z }; }
        Vector FlipZ() const { return { x, y, -z }; }

        Vector Cross(const Vector& other) const {
            return {
                (T)(y * other.z - z * other.y),
                (T)(z * other.x - x * other.z),
                (T)(x * other.y - y * other.x),
            };
        }
        Vector AnyPerpend() const requires Floating<T> {
            // https://math.stackexchange.com/a/4112622
            return {
                NumInfo<T>::CopySign(z, x),
                NumInfo<T>::CopySign(z, y),
                -NumInfo<T>::CopySign(std::abs(x) + std::abs(y), z),
            };
        }
        // takes in a normal and returns a perpendicular normal
        Vector AnyTangent() const requires Floating<T> {
            const T sign = std::copysign(1, z), a = -1 / (sign + z);
            return { x * y * a, sign + y * y * a, -y };
        }
        // this is normalized for you!
        Tuple<Vector, Vector> AnyOrthoBasis() const requires Floating<T> {
            // https://graphics.pixar.com/library/OrthonormalB/paper.pdf
            const T sign = std::copysign(1, z), a = -1 / (sign + z), b = x * y * a;
            return { Vector { 1 + sign * x * x * a, sign * b, -sign * x },
                     Vector { b, sign + y * y * a, -y } };
        }

        Radians SignedAngleBetween(const Vector& other, const Vector& normal) const {
            return Trig::Atan2((fT)Cross(other).Dot(normal), (fT)this->Dot(other));
        }
        Radians Yaw()   const { return Trig::Atan2(x, z); }
        Radians Pitch() const { return Trig::Atan2(y, std::sqrt(x * x + z * z)); }
        Tuple<fT, Radians, Radians> SphericCoords() const requires Floating<T> {
            const fT len = this->Len();
            return { len, Yaw(), Trig::Arcsin(y / len) };
        }
        static Vector FromSpheric(T r, Radians yaw, Radians pitch) requires Floating<T> {
            const T xz = r * Cos(pitch);
            return { xz * Cos(yaw), r * Sin(pitch), xz * Sin(yaw) };
        }
        static Vector FromSpheric(T r, const Rotor2D& yaw, const Rotor2D& pitch) requires Floating<T>;
        Vec2<fT> ProjectTo2DPlane() const { const fT invZ = (fT)1 / z; return { x * invZ, y * invZ }; }

        Vec2<T> As2D() const { return { x, y }; }
        Vec4<T> AddW(T w = 1) const { return { x, y, z, w }; }

        bool operator==(const Vector&) const = default;
    };

    template <class T> struct Vector<T, 3> { T x, y, z; };

    template <Numeric T> struct Vector<T, 4> : IVector<T, 4> {
        friend IVector<T, 4>;
        using fT = typename IVector<T, 2>::fT;
        T x, y, z, w;
    protected:
        T* DataImpl() { return &x; }
        const T* DataImpl() const { return &x; }
        static usize CompFromNameImpl(char c) {
            switch (c) {
                case 'x': case 's': case 'r': return 0;
                case 'y': case 't': case 'g': return 1;
                case 'z': case 'u': case 'b': return 2;
                case 'w': case 'v': case 'a': return 3;
                default: return -1;
            }
        }
    public:
        Vector(T s = 0, T w = 0) : x(s), y(s), z(s), w(w) {}
        Vector(T x, T y, T z, T w = 1) : x(x), y(y), z(z), w(w) {}
        Vector(const Vector<T, 3>& xyz, T w = 1) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

        static Vector XAxis() { return { 1, 0, 0, 0 }; }
        static Vector YAxis() { return { 0, 1, 0, 0 }; }
        static Vector ZAxis() { return { 0, 0, 1, 0 }; }
        static Vector WAxis() { return { 0, 0, 0, 1 }; }
        static Vector XPos()                    { return { +1,  0,  0,  0 }; } static Vector Right()                   { return XPos(); }
        static Vector XNeg() requires Signed<T> { return { -1,  0,  0,  0 }; } static Vector Left() requires Signed<T> { return XNeg(); }
        static Vector YPos()                    { return {  0, +1,  0,  0 }; } static Vector Up()                      { return YPos(); }
        static Vector YNeg() requires Signed<T> { return {  0, -1,  0,  0 }; } static Vector Down() requires Signed<T> { return YNeg(); }
        static Vector ZPos()                    { return {  0,  0, +1,  0 }; } static Vector Front()                   { return ZPos(); }
        static Vector ZNeg() requires Signed<T> { return {  0,  0, -1,  0 }; } static Vector Back() requires Signed<T> { return ZNeg(); }
        static Vector WPos()                    { return {  0,  0,  0, +1 }; } static Vector In()                      { return WPos(); }
        static Vector WNeg() requires Signed<T> { return {  0,  0,  0, -1 }; } static Vector Out()  requires Signed<T> { return WNeg(); }

        Vector FlipX() const { return { -x, y, z, w }; }
        Vector FlipY() const { return { x, -y, z, w }; }
        Vector FlipZ() const { return { x, y, -z, w }; }
        Vector FlipW() const { return { x, y, z, -w }; }

        Vec3<fT> ProjectTo3DPlane() const { const fT invW = (fT)1 / w; return { x * invW, y * invW, z * invW }; }
        Vec3<T> As3D() const { return { x, y, z }; }
        Vec2<T> As2D() const { return { x, y }; }

        bool operator==(const Vector&) const = default;
    };

    template <class T> struct Vector<T, 4> { T x, y, z, w; };

    struct VectorFormatter {
        struct FormatOptions {
            Str elementFmt = "#: $", separator = ", ";
        };
        static FormatOptions ConfigureOptions(Str opt);
        template <class T>
        static usize FormatToInternal(Text::StringWriter sw, Span<const T> vector, Str comps, const FormatOptions& options) {
            OptionUsize identifiers[2] {};
            for (usize i = 0, j = 0; i < options.elementFmt.Length(); ++i) {
                const char c = options.elementFmt[i];
                if (c == '$' || c == '#') {
                    identifiers[j] = i;
                    if (++j == 2) break;
                }
            }
            Str sections[3] = {};
            if (identifiers[0]) {
                sections[0] = options.elementFmt.First(*identifiers[0]);
                if (identifiers[1]) {
                    sections[1] = options.elementFmt.Substr(*identifiers[0] + 1, *identifiers[1] - *identifiers[0] - 1);
                    sections[2] = options.elementFmt.Skip(*identifiers[1] + 1);
                } else {
                    sections[1] = options.elementFmt.Skip(*identifiers[0] + 1);
                }
            } else {
                sections[0] = options.elementFmt;
            }

            usize ln = (sections[0].Length() + sections[1].Length() + sections[2].Length() + options.separator.Length());
            ln *= vector.Length();
            ln -= options.separator.Length();
            for (usize i = 0; i < vector.Length(); i++) {
                if (i != 0)
                    sw.Write(options.separator);

                sw.Write(sections[0]);
                if (identifiers[0]) {
                    if (options.elementFmt[*identifiers[0]] == '#') {
                        ln += sw.Write(comps[i]);
                    } else {
                        ln += Text::FormatObjectTo(sw, vector[i]);
                    }
                }
                sw.Write(sections[1]);
                if (*identifiers[1]) {
                    if (options.elementFmt[*identifiers[1]] == '#') {
                        ln += sw.Write(comps[i]);
                    } else {
                        ln += Text::FormatObjectTo(sw, vector[i]);
                    }
                }
                sw.Write(sections[2]);
            }
            return ln;
        }
    };
}

namespace Quasi::Text {
    template <class T, usize N>
    struct Formatter<Math::Vector<T, N>> : Math::VectorFormatter {
        static usize FormatTo(StringWriter sw, const Math::Vector<T, N>& vec, const FormatOptions& options) {
            return VectorFormatter::FormatToInternal(sw, vec.AsSpan(), Str::Slice("xyzw", N), options);
        }
    };

    template <class T, usize N>
    struct Parser<Math::Vector<T, N>> {
        using ParseOptions = Str;
        static OptionUsize ParseUntil(Str s, Out<Math::Vector<T, N>&> out, Str) {
            Option<Math::Vector<T, N>> v = Math::Vector<T, N>::Parse(s, ", ");
            if (!v) return nullptr;
            out = *v;
            return s.Length();
        }
    };
}