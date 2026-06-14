#pragma once
#include "Vector.h"
#include "Utils/Match.h"

namespace Quasi::Math {
    namespace Colors { enum ColorID : u32; }

    template <class T, bool HasAlpha>
    struct IColor {
        T r = 0, g = 0, b = 0;
        [[no_unique_address]]
        IfElse<HasAlpha, T, Empty> a = 0;

        using Elm = T;
        enum { Dim = 3 + HasAlpha };
        static constexpr bool NoAlpha = !HasAlpha;
    public:
        IColor() = default;
        IColor(T s, T a = 1) requires HasAlpha : r(s), g(s), b(s), a(a) {}
        IColor(T s)          requires NoAlpha  : r(s), g(s), b(s) {}
        IColor(T r, T g, T b, T a = 1) requires HasAlpha : r(r), g(g), b(b), a(a) {}
        IColor(T r, T g, T b, T   = 1) requires NoAlpha : r(r), g(g), b(b) {}
        IColor(const Vec4<T>& rgba)     requires HasAlpha : r(rgba.x), g(rgba.y), b(rgba.z), a(rgba.w) {}
        IColor(const Vec3<T>& rgb, T a) requires HasAlpha : r(rgb.x),  g(rgb.y),  b(rgb.z),  a(a) {}
        IColor(const Vec3<T>& rgb)                        : r(rgb.x),  g(rgb.y),  b(rgb.z) {}

        static usize CompFromName(char c) { return Vector<T, Dim>::CompFromName(c); }
        T*       Data()          { return &r; }
        const T* Data() const    { return &r; }
        T*       DataEnd()       { return &r + Dim; }
        const T* DataEnd() const { return &r + Dim; }
        Span<const T> AsSpan() const { return Spans::Slice(Data(), 3 + Dim); }
        Span<T>       AsSpan()       { return Spans::Slice(Data(), 3 + Dim); }

        T&       At(usize i)       { return Data()[i]; }
        const T& At(usize i) const { return Data()[i]; }
        T&       operator[](usize i)       { return Data()[i]; }
        const T& operator[](usize i) const { return Data()[i]; }

        template <class U> U ChannelAs(usize i) const {
            if constexpr (Floating<T>) {
                if constexpr (Floating<U>) return At(i); else return (U)f32s::FastToIntUnsigned(std::clamp(At(i), 0.0f, 1.0f) * 255.0f);
            } else {
                if constexpr (Floating<U>) return At(i) / 255.0f; else return (U)At(i);
            }
        }
        template <class U> U RedAs()   const { return ChannelAs<U>(0); }
        template <class U> U GreenAs() const { return ChannelAs<U>(1); }
        template <class U> U BlueAs()  const { return ChannelAs<U>(2); }
        template <class U> U AlphaAs() const requires HasAlpha { return ChannelAs<U>(3); }
        template <class U = T> U AlphaOrFull() const {
            if constexpr (HasAlpha) return AlphaAs<U>();
            else if constexpr (Floating<U>) return 1.0f;
            else return (U)255;
        }

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

        usize Dimensions() const { return Dim; }

        static IColor FromSpan(Span<const T> elms) {
            IColor c;
            Memory::RangeCopy(c.Data(), elms.Data(), std::min<usize>(elms.Length(), Dim));
            return c;
        }
        static IColor Greyscale(T scale) {
            IColor v;
            Memory::RangeSet(v.Data(), scale, Dim);
            return v;
        }

        IColor<T, true> AddAlpha(T alpha) const {
            return { r, g, b, alpha };
        }
        IColor<T, false> RemAlpha() const requires NoAlpha {
            return { r, g, b };
        }

        Vector<T, Dim> AsVector() const {
            if constexpr (HasAlpha) return { r, g, b, a };
            else return { r, g, b };
        }
        template <class C> C As() const {
            using U = decltype(C {}.r);
            return { RedAs<U>(), GreenAs<U>(), BlueAs<U>(), AlphaOrFull<U>() };
        }
        template <class C> operator C() const { return As<C>(); }

        bv3 AsRGBVec()   const;
        bv4 AsRGBAVec()  const;
        fv3 AsRGBfVec()  const;
        fv4 AsRGBAfVec() const;
        Tuple<f32, f32, f32>      GetHSL()  const;
        Tuple<f32, f32, f32, f32> GetHSLA() const;
        static IColor FromHSL (f32 hue, f32 saturation = 1, f32 lightness = 1); /* hue: [0-1], sat: [0-1], L: [0-1] */
        static IColor FromHSLA(f32 hue, f32 saturation = 1, f32 lightness = 1, f32 alpha = 1); /* hue: [0-1], sat: [0-1], L: [0-1] */
        Tuple<f32, f32, f32>      GetHSV()  const;
        Tuple<f32, f32, f32, f32> GetHSVA() const;
        static IColor FromHSV (f32 hue, f32 saturation = 1, f32 value = 1); /* hue: [0-1], sat: [0-1], val: [0-1] */
        static IColor FromHSVA(f32 hue, f32 saturation = 1, f32 value = 1, f32 alpha = 1); /* hue: [0-1], sat: [0-1], val: [0-1] */

        Comparison Cmp(const IColor& other) const { return AsSpan().Cmp(other.AsSpan()); }

        IColor Add(const IColor& other) const;
        IColor Sub(const IColor& other) const;
        IColor Mul(T scale)   const;
        IColor Mul(f32 scale) const requires Integer<T>;
        IColor Div(T scale)   const;
        IColor Div(f32 scale) const requires Integer<T>;
        IColor AddScalar(T off) const;
        IColor SubScalar(T off) const;

        IColor& AddAssign(const IColor& other);
        IColor& SubAssign(const IColor& other);
        IColor& MulAssign(T scale);
        IColor& MulAssign(f32 scale) requires Integer<T>;
        IColor& DivAssign(T scale);
        IColor& DivAssign(f32 scale) requires Integer<T>;
        IColor& AddScalarAssign(T off);
        IColor& SubScalarAssign(T off);

        IColor operator+() const { return *this; }

        IColor operator+(const IColor& other) const { return Add(other); }
        IColor operator+(T off)              const { return AddScalar(off); }
        IColor operator-(const IColor& other) const { return Sub(other); }
        IColor operator-(T off)              const { return SubScalar(off); }
        IColor operator*(const IColor& other) const { return Product(other); }
        IColor operator*(T scale)            const { return Mul(scale); }
        IColor operator*(f32 scale) const requires Integer<T> { return Mul(scale); }
        IColor operator/(T scale)            const { return Div(scale); }
        IColor operator/(f32 scale) const requires Integer<T> { return Div(scale); }

        IColor& operator+=(const IColor& other) { return AddAssign(other); }
        IColor& operator+=(T off)               { return AddScalarAssign(off); }
        IColor& operator-=(const IColor& other) { return SubAssign(other); }
        IColor& operator-=(T off)               { return SubScalarAssign(off); }
        IColor& operator*=(const IColor& other) { return *this = Product(other); }
        IColor& operator*=(T scale)             { return MulAssign(scale); }
        IColor& operator*=(f32 scale) requires Integer<T> { return MulAssign(scale); }
        IColor& operator/=(T scale)             { return DivAssign(scale); }
        IColor& operator/=(f32 scale) requires Integer<T> { return DivAssign(scale); }

        IColor Map(T other, const FnArgs<T, T> auto& mapping) const {
            if constexpr (HasAlpha)
                return { mapping(r, other), mapping(g, other), mapping(b, other), mapping(a, other) };
            else return { mapping(r, other), mapping(g, other), mapping(b, other) };
        }
        IColor BinaryMap(const IColor& other, const FnArgs<T, T> auto& mapping) const {
            if constexpr (HasAlpha)
                return { mapping(r, other.r), mapping(g, other.g), mapping(b, other.b), mapping(a, other.a) };
            else return { mapping(r, other.r), mapping(g, other.g), mapping(b, other.b) };
        }
        IColor MapRGB(T other, const FnArgs<T, T> auto& mapping, T alpha) const {
            return { mapping(r, other), mapping(g, other), mapping(b, other), alpha };
        }
        IColor BinaryMapRGB(const IColor& other, const FnArgs<T, T> auto& mapping, T alpha) const {
            return { mapping(r, other.r), mapping(g, other.g), mapping(b, other.b), alpha };
        }

        IColor Inverted() const;
        IColor Lerp(const IColor& other, f32 t) const;
        IColor Lerp(const IColor& other, int p, int q) const;
        IColor& LerpTowards(const IColor& other, f32 t);
        IColor Blend(const IColor& top) requires HasAlpha;
        IColor LogBlend(const IColor& other, f32 t) const;
        IColor LogBlend(const IColor& other, int p, int q) const;
        IColor AdjustShade(int brightOff) const requires Integer<T>;
        IColor AdjustShade(f32 brightOff) const requires Floating<T>;
        IColor Product(const IColor& other) const;
        IColor Screen (const IColor& other) const;
        IColor Over   (const IColor& other) const;
        IColor<T, false> MulAlpha() const;
        f32 Luminance() const;

        static IColor FromBytes(u8 r, u8 g, u8 b, u8 a = 255);
        static IColor FromIntCode(u32 rgb, u8 a = 255);
        static IColor FromIntWithAlpha(u32 rgba);
        static IColor FromIntLittleCode(u32 bgr, u8 a = 255);
        static IColor FromIntLittleWithAlpha(u32 abgr);
        static IColor FromFloats(f32 r, f32 g, f32 b, f32 a = 1.0f);
        static Option<IColor> FromHex(Str hex);
        u32    GetIntCode() const; // returns in format 0xRRGGBBAA
        String GetHexCode() const;

        bool operator==(const IColor&) const = default;
        bool LooseEq(const IColor& other) const;


        static IColor Random(RandomGenerator& rand);
        static IColor RandomPure(RandomGenerator& rand);

#pragma region Colors
        static IColor Clear()        { return { 0, 0, 0, 0 }; } // complete transparency. RGBA is (0, 0, 0, 0)
        static IColor Black()        { return FromIntCode(0x000000); } // solid black: rgb(000, 000, 000) or #000000
        static IColor DarkGray()     { return FromIntCode(0x404040); } // 25% white:   rgb(064, 064, 064) or #404040
        static IColor Gray()         { return FromIntCode(0x808080); } // 50% white:   rgb(128, 128, 128) or #808080
        static IColor LightGray()    { return FromIntCode(0xc0c0c0); } // 75% white:   rgb(192, 192, 192) or #c0c0c0
        static IColor White()        { return FromIntCode(0xffffff); } // solid white: rgb(255, 255, 255) or #ffffff
        static IColor Red()          { return FromIntCode(0xff0000); } // red    (100%   red):              rgb(255, 000, 000) or #ff0000
        static IColor Orange()       { return FromIntCode(0xff8000); } // orange (100%   red +  50% green): rgb(255, 128, 000) or #ff8000
        static IColor Yellow()       { return FromIntCode(0xffff00); } // yellow (100%   red + 100% green): rgb(255, 255, 000) or #ffff00
        static IColor Lime()         { return FromIntCode(0x80ff00); } // lime   (100% green +  50%   red): rgb(128, 255, 000) or #80ff00
        static IColor Green()        { return FromIntCode(0x00ff00); } // green  (100% green):              rgb(000, 255, 000) or #00ff00
        static IColor Seafoam()      { return FromIntCode(0x00ff80); } // seafoam(100% green +  50%  blue): rgb(000, 255, 128) or #00ff80
        static IColor Aqua()         { return FromIntCode(0x00ffff); } // aqua   (100% green + 100%  blue): rgb(000, 255, 255) or #00ffff
        static IColor Cyan()         { return FromIntCode(0x0080ff); } // cyan   (100%  blue +  50% green): rgb(000, 128, 255) or #0080ff
        static IColor Blue()         { return FromIntCode(0x0000ff); } // blue   (100%  blue):              rgb(000, 000, 255) or #0000ff
        static IColor Purple()       { return FromIntCode(0x8000ff); } // purple (100%  blue +  50%   red): rgb(128, 000, 255) or #8000ff
        static IColor Magenta()      { return FromIntCode(0xff00ff); } // magenta(100%  blue + 100%   red): rgb(255, 000, 255) or #ff00ff
        static IColor Rose()         { return FromIntCode(0xff0080); } // rose   (100%   red +  50%  blue): rgb(255, 000, 128) or #ff0080
        static IColor LightRed()     { return FromIntCode(0xff8080); } // light red    (100%   red +  50% green +  50%  blue): rgb(255, 128, 128) or #ff8080
        static IColor LightYellow()  { return FromIntCode(0xffff80); } // light yellow (100%   red + 100% green +  50%  blue): rgb(255, 255, 128) or #ffff80
        static IColor LightGreen()   { return FromIntCode(0x80ff80); } // light green  ( 50%   red + 100% green +  50%  blue): rgb(128, 255, 128) or #80ff80
        static IColor LightAqua()    { return FromIntCode(0x80ffff); } // light aqua   ( 50%   red + 100% green + 100%  blue): rgb(128, 255, 255) or #80ffff
        static IColor LightBlue()    { return FromIntCode(0x4080ff); } // light blue   ( 25%   red +  50% green + 100%  blue): rgb( 64, 128, 255) or #4080ff (manually adjusted)
        static IColor LightMagenta() { return FromIntCode(0xff80ff); } // light magenta(100%   red +  50% green + 100%  blue): rgb(255, 128, 255) or #ff80ff
        static IColor DarkRed()      { return FromIntCode(0x800000); } // dark red   ( 50%   red):              rgb(128, 000, 000) or #800000
        static IColor DarkYellow()   { return FromIntCode(0x808000); } // dark yellow( 50%   red +  50% green): rgb(128, 128, 000) or #808000
        static IColor DarkGreen()    { return FromIntCode(0x008000); } // dark green ( 50% green):              rgb(000, 128, 000) or #008000
        static IColor DarkCyan()     { return FromIntCode(0x008080); } // dark cyan  ( 50% green +  50%  blue): rgb(000, 128, 128) or #008080
        static IColor DarkBlue()     { return FromIntCode(0x000080); } // dark blue  ( 50%  blue):              rgb(000, 000, 128) or #000080
        static IColor DarkMagenta()  { return FromIntCode(0x800080); } // dark purple( 50%  blue +  50%   red): rgb(128, 000, 128) or #800080
        static IColor Silver()       { return FromIntCode(0xc0c0c0); } // same as light gray,    rgb(192, 192, 192) or #c0c0c0
        static IColor Salmon()       { return FromIntCode(0xff8080); } // same as light red,     rgb(255, 128, 128) or #ff8080
        static IColor Lemon()        { return FromIntCode(0xffff80); } // same as light yellow,  rgb(255, 255, 128) or #ffff80
        static IColor Mint()         { return FromIntCode(0x80ff80); } // same as light green,   rgb(128, 255, 128) or #80ff80
        static IColor Sky()          { return FromIntCode(0x80ffff); } // same as light cyan,    rgb(128, 255, 255) or #80ffff
        static IColor Cornflower()   { return FromIntCode(0x8080ff); } // same as light blue,    rgb(128, 128, 255) or #8080ff
        static IColor Pink()         { return FromIntCode(0xff80ff); } // same as light magenta, rgb(255, 128, 255) or #ff80ff
        static IColor Maroon()       { return FromIntCode(0x800000); } // same as dark red,      rgb(128, 000, 000) or #800000
        static IColor Olive()        { return FromIntCode(0x808000); } // same as dark yellow,   rgb(128, 128, 000) or #808000
        static IColor Avocado()      { return FromIntCode(0x008000); } // same as dark green,    rgb(000, 128, 000) or #008000
        static IColor Teal()         { return FromIntCode(0x008080); } // same as dark cyan,     rgb(000, 128, 128) or #008080
        static IColor Navy()         { return FromIntCode(0x000080); } // same as dark blue,     rgb(000, 000, 128) or #000080
        static IColor Violet()       { return FromIntCode(0x800080); } // same as dark purple,   rgb(128, 000, 128) or #800080
        struct Better {
            static IColor Red()        { return IColor::FromIntCode(0xff3030); } // #ff3030, or rgb(255, 048, 048)
            static IColor Orange()     { return IColor::FromIntCode(0xff802b); } // #ff802b, or rgb(255, 128, 043)
            static IColor Yellow()     { return IColor::FromIntCode(0xffc014); } // #ffc014, or rgb(255, 192, 020)
            static IColor Lime()       { return IColor::FromIntCode(0x87f725); } // #87f725, or rgb(135, 247, 037)
            static IColor Green()      { return IColor::FromIntCode(0x0c8501); } // #0c8501, or rgb(012, 133, 001)
            static IColor Aqua()       { return IColor::FromIntCode(0x28cef7); } // #28cef7, or rgb(040, 206, 247)
            static IColor Cyan()       { return IColor::FromIntCode(0x17a0b3); } // #17a0b3, or rgb(023, 160, 179)
            static IColor Blue()       { return IColor::FromIntCode(0x1041e3); } // #1041e3, or rgb(016, 065, 227)
            static IColor Purple()     { return IColor::FromIntCode(0x7818ed); } // #7818ed, or rgb(120, 024, 237)
            static IColor Magenta()    { return IColor::FromIntCode(0xcb2aeb); } // #cb2aeb, or rgb(203, 042, 235)
            static IColor Pink()       { return IColor::FromIntCode(0xfa57c6); } // #fa57c6, or rgb(250, 087, 198)
            static IColor Brown()      { return IColor::FromIntCode(0x45200d); } // #45200d, or rgb(069, 032, 013)
            static IColor Black()      { return IColor::FromIntCode(0x16191d); } // #16191d, or rgb(022, 025, 029)
            static IColor DarkGray()   { return IColor::FromIntCode(0x4c4b5d); } // #4c4b5d, or rgb(076, 075, 093)
            static IColor Gray()       { return IColor::FromIntCode(0x747e86); } // #747e86, or rgb(116, 126, 134)
            static IColor LightGray()  { return IColor::FromIntCode(0xafbac1); } // #afbac1, or rgb(175, 186, 193)
            static IColor White()      { return IColor::FromIntCode(0xe8f7f9); } // #e8f7f9, or rgb(232, 247, 249)
            inline static IColor Colors[] {
                Red(), Orange(), Yellow(), Lime(), Green(), Aqua(), Cyan(), Blue(), Purple(), Magenta(), Pink(), Brown(), Black(), DarkGray(), Gray(), LightGray(), White(),
            };
        };
        struct Atom {
            static IColor Red()         { return IColor::FromIntCode(0xe06c75); } // #e06c75, or rgb(224, 108, 117)
            static IColor Orange()      { return IColor::FromIntCode(0xd19a66); } // #d19a66, or rgb(209, 154, 102)
            static IColor Green()       { return IColor::FromIntCode(0x98c379); } // #98c379, or rgb(152, 195, 121)
            static IColor Aqua()        { return IColor::FromIntCode(0x56b6c2); } // #56b6c2, or rgb( 86, 182, 194)
            static IColor Purple()      { return IColor::FromIntCode(0xc678dd); } // #c678dd, or rgb(198, 120, 221)
            static IColor Blue()        { return IColor::FromIntCode(0x61afef); } // #61afef, or rgb( 97, 175, 239)
            static IColor Yellow()      { return IColor::FromIntCode(0xe5c07b); } // #e5c07b, or rgb(229, 192, 123)
            static IColor Gray()        { return IColor::FromIntCode(0xabb2bf); } // #abb2bf, or rgb(171, 178, 191)
            static IColor DarkRed()     { return IColor::FromIntCode(0xbe5046); } // #be5046, or rgb(190,  80,  70)
            static IColor DarkOrange()  { return IColor::FromIntCode(0xd19a66); } // #d19a66, or rgb(209, 154, 102)
            static IColor DarkGreen()   { return IColor::FromIntCode(0x7a9f60); } // #7a9f60, or rgb(122, 159,  96)
            static IColor DarkAqua()    { return IColor::FromIntCode(0x3c909b); } // #3c909b, or rgb( 60, 144, 155)
            static IColor DarkPurple()  { return IColor::FromIntCode(0x9a52af); } // #9a52af, or rgb(154,  82, 175)
            static IColor DarkBlue()    { return IColor::FromIntCode(0x3b84c0); } // #3b84c0, or rgb( 59, 132, 192)
            static IColor DarkYellow()  { return IColor::FromIntCode(0xd19a66); } // #d19a66, or rgb(209, 154, 102)
            static IColor DarkGray()    { return IColor::FromIntCode(0x5C6370); } // #5C6370, or rgb( 92,  99, 112)
            static IColor Background()  { return IColor::FromIntCode(0x272b34); } // #272b34, or rgb( 39,  43,  52)
            static IColor BgSecondary() { return IColor::FromIntCode(0x20242b); } // #20242b, or rgb( 32,  36,  43)
            static IColor BgAlt()       { return IColor::FromIntCode(0x1a1e24); } // #1a1e24, or rgb( 26,  30,  36)
            static IColor Text()        { return IColor::FromIntCode(0xdcddde); } // #dcddde, or rgb(220, 221, 222)
        };
#pragma endregion
    };

    using fColor  = IColor<f32, true>;
    using uColor  = IColor<u8, true>;
    using fColor3 = IColor<f32, false>;
    using uColor3 = IColor<u8, false>;

    uColor3 operator ""_rgb(usize x);
    uColor  operator ""_rgba(usize x);
    fColor3 operator ""_rgbf(usize x);
    fColor  operator ""_rgbaf(usize x);
}

namespace Quasi::Text {
    template <class T, bool A>
    struct Formatter<Math::IColor<T, A>> : Math::VectorFormatter {
        static usize FormatTo(StringWriter sw, const Math::IColor<T, A>& vec, const FormatOptions& options) {
            return VectorFormatter::FormatToInternal(sw, vec.AsSpan(), Str::Slice("rgba", 3 + A), options);
        }
    };
}