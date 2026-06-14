#include "Color.h"

#include "Random.h"
#include "Utils/Text.h"

namespace Quasi::Math {
#pragma region Conversion
    template <class T> T ChannelConv(f32 channel) {
        if constexpr (Floating<T>) return channel;
        else {
            u32 x = f32s::FastToIntUnsigned(channel * 255.0f);
            return x > 255 ? (T)255 : (T)x;
        }
    }

    template <class T> T ByteConv(u8 channel) {
        if constexpr (Integer<T>) return channel;
        else return (f32)channel / 255.0f;
    }

    Tuple<f32, f32, f32> RGB2HSL(f32 r, f32 g, f32 b) {
        // https://stackoverflow.com/a/9493060
        const f32 max = std::max({ r, g, b }), min = std::min({ r, g, b });
        f32 h = 0, l = (max + min) / 2;

        if (max == min)
            return { 0, 0, l }; // achromatic

        const f32 d = max - min;
        f32 s = d / (l > 0.5f ? (2 - max - min) : (max + min));
        if (max == r) h = (g - b) / d + (g < b ? 6.0f : 0.0f);
        if (max == g) h = (b - r) / d + 2;
        if (max == b) h = (r - g) / d + 4;
        h /= 6;

        return { h, s, l };
    }

    f32 Hue2RGB(f32 p, f32 q, f32 t) {
        if (t < 0) t += 1;
        if (t > 1) t -= 1;
        if (t < 1.0f/6) return p + (q - p) * 6 * t;
        if (t < 1.0f/2) return q;
        if (t < 2.0f/3) return p + (q - p) * (2.0f/3 - t) * 6;
        return p;
    }

    Tuple<f32, f32, f32> HSL2RGB(f32 h, f32 s, f32 l) {
        f32 r, g, b;
        if (s == 0) {
            r = g = b = l; // achromatic
        } else {
            const f32 q = l < 0.5 ? l * (1 + s) : l + s - l * s;
            const f32 p = 2 * l - q;
            r = Hue2RGB(p, q, h + 1.0f/3);
            g = Hue2RGB(p, q, h);
            b = Hue2RGB(p, q, h - 1.0f/3);
        }
        return { r, g, b };
    }

    Tuple<f32, f32, f32> RGB2HSV(f32 r, f32 g, f32 b) {
        // https://stackoverflow.com/a/6930407
        const f32 max = std::max({ r, g, b }), min = std::min({ r, g, b });
        const f32 v = max, d = max - min;
        if (v == 0)
            return { f32s::NAN, 0, v }; // acromatic
        f32 s = d / v;
        if (d == 0)
            return { 0, 0, v }; // acromatic
        f32 h = 0;
        if (max == r) h = g - b;
        else if (max == g) h = 2 + b - r;
        else if (max == b) h = 4 + r - g;
        h /= d * 6;
        h += (f32)(h < 0);
        return { h, s, v };
    }
    Tuple<f32, f32, f32> HSV2RGB(f32 h, f32 s, f32 v) {
        if (s == 0)
            return { v, v, v }; // Achromatic case
        h *= 6;
        const int i = (int)h;
        const f32 f = h - (f32)i;
        f32 p = v * (1 - s);
        f32 q = v * (1 - f * s);
        f32 t = v * (1 - (1 - f) * s);
        switch (i) {
            case 0:  return { v, t, p };
            case 1:  return { q, v, p };
            case 2:  return { p, v, t };
            case 3:  return { p, q, v };
            case 4:  return { t, p, v };
            case 5:  return { v, p, q };
            default: return { 0, 0, 0 };
        }
    }
#pragma endregion

#define coldef template <class T, bool HasAlpha>
#define colcls IColor<T, HasAlpha>
    coldef bv3 colcls::AsRGBVec()   const { return { RedAs<u8>(),  GreenAs<u8>(),  BlueAs<u8>() }; }
    coldef bv4 colcls::AsRGBAVec()  const { return { RedAs<u8>(),  GreenAs<u8>(),  BlueAs<u8>(),  AlphaOrFull<u8>() }; }
    coldef fv3 colcls::AsRGBfVec()  const { return { RedAs<f32>(), GreenAs<f32>(), BlueAs<f32>() }; }
    coldef fv4 colcls::AsRGBAfVec() const { return { RedAs<f32>(), GreenAs<f32>(), BlueAs<f32>(), AlphaOrFull<f32>() }; }
    coldef Tuple<f32, f32, f32> colcls::GetHSL()  const {
        return RGB2HSL(RedAs<f32>(), GreenAs<f32>(), BlueAs<f32>());
    }
    coldef Tuple<f32, f32, f32, f32> colcls::GetHSLA() const {
        const auto [h, s, l] = RGB2HSL(RedAs<f32>(), GreenAs<f32>(), BlueAs<f32>());
        return { h, s, l, AlphaOrFull<f32>() };
    }
    coldef colcls colcls::FromHSL (f32 hue, f32 saturation, f32 lightness) {
        const auto [r, g, b] = HSL2RGB(hue, saturation, lightness);
        return { ChannelConv<T>(r), ChannelConv<T>(g), ChannelConv<T>(b) };
    }
    coldef colcls colcls::FromHSLA(f32 hue, f32 saturation, f32 lightness, f32 alpha) {
        const auto [r, g, b] = HSL2RGB(hue, saturation, lightness);
        return { ChannelConv<T>(r), ChannelConv<T>(g), ChannelConv<T>(b), ChannelConv<T>(alpha) };
    }
    coldef Tuple<f32, f32, f32> colcls::GetHSV() const {
        return RGB2HSV(RedAs<f32>(), GreenAs<f32>(), BlueAs<f32>());
    }
    coldef Tuple<f32, f32, f32, f32> colcls::GetHSVA() const {
        const auto [h, s, v] = RGB2HSV(RedAs<f32>(), GreenAs<f32>(), BlueAs<f32>());
        return { h, s, v, AlphaOrFull<f32>() };
    }
    coldef colcls colcls::FromHSV(f32 hue, f32 saturation, f32 value) {
        const auto [r, g, b] = HSV2RGB(hue, saturation, value);
        return { ChannelConv<T>(r), ChannelConv<T>(g), ChannelConv<T>(b) };
    }
    coldef colcls colcls::FromHSVA(f32 hue, f32 saturation, f32 value, f32 alpha) {
        const auto [r, g, b] = HSV2RGB(hue, saturation, value);
        return { ChannelConv<T>(r), ChannelConv<T>(g), ChannelConv<T>(b), ChannelConv<T>(alpha) };
    }

#pragma region Operations
#define CHANNEL_OP(NAME, SECOND_ARG, U8, F32) \
    struct NAME { u8 operator()(u8 a, SECOND_ARG(u8) b) const { (void)b; return U8; } f32 operator()(f32 a, SECOND_ARG(f32) b) const { (void)b; return F32; } };
#define BINARY(X) X
#define FLOAT_OP(X) f32
    CHANNEL_OP(ChannelAdd, BINARY, a + b > 255 ? 255_u8 : (u8)(a + b), a + b)
    CHANNEL_OP(ChannelSub, BINARY, b > a       ?   0_u8 : (u8)(a - b), a - b)
    CHANNEL_OP(ChannelMul, BINARY, (u8)(a * b / 255),                  a * b)
    CHANNEL_OP(ChannelDiv, BINARY, (u8)(a * 255 / b),                  a / b)

    CHANNEL_OP(ChannelMulF, FLOAT_OP, a * b > 255.0f ? 255_u8 : ChannelConv<u8>(a * b), a * b)
    CHANNEL_OP(ChannelScreen, BINARY, 255 - (255 - a) * (255 * b) / 255, 1 - (1 - a) * (1 - b))

    CHANNEL_OP(ChannelInv, BINARY, (u8)~a, 1.0f - a)
    struct ChannelLerp {
        f32 t, tCompl;
        u8 operator()(u8 a, u8 b) const {
            const f32 v = tCompl * (f32)a + t * (f32)b;
            if (v < 0 || v > 255.0f) return v < 0 ? 0_u8 : 255_u8;
            return (u8)f32s::FastToIntUnsigned(v);
        }
        f32 operator()(f32 a, f32 b) const { return a * tCompl + b * t; }
    };
    struct ChannelLerpFraction {
        int p, pCompl, q;
        u8 operator()(u8 a, u8 b) const {
            const int v = (pCompl * a + p * b) / q;
            if (v < 0 || v > 255) return v < 0 ? 0_u8 : 255_u8;
            return (u8)v;
        }
    };
    struct ChannelLogBlend {
        f32 t, tCompl;
        u8 operator()(u8 a, u8 b) const {
            const f32 v = std::sqrt(tCompl * (f32)(a * a) + t * (f32)(b * b));
            if (v < 0 || v > 255.0f) return v < 0 ? 0_u8 : 255_u8;
            return (u8)f32s::FastToIntUnsigned(v);
        }
        f32 operator()(f32 a, f32 b) const { return std::sqrt(a * a * tCompl + b * b * tCompl); }
    };
    struct ChannelLogBlendFraction {
        int p, pCompl, q;
        u8 operator()(u8 a, u8 b) const {
            const int v = (int)std::sqrt((pCompl * a * a + p * b * b) / q);
            if (v < 0 || v > 255) return v < 0 ? 0_u8 : 255_u8;
            return (u8)v;
        }
    };
    struct ChannelAdjust {
        u8 operator()(u8 a, int b) const { const int v = a + b; return v > 255 ? 255_u8 : v < 0 ? 0 : (u8)v; }
        f32 operator()(f32 a, f32 b) const { return a + b; }
    };
#pragma endregion

    coldef colcls colcls::Add(const IColor& other) const { return BinaryMap(other, ChannelAdd {}); }
    coldef colcls colcls::Sub(const IColor& other) const { return BinaryMap(other, ChannelSub {}); }
    coldef colcls colcls::Mul(T scale)             const { return Map      (scale, ChannelMul {}); }
    coldef colcls colcls::Mul(f32 scale) const requires Integer<T> { return Map(scale, ChannelMulF {}); }
    coldef colcls colcls::Div(T scale)             const { return Map      (scale, ChannelDiv {}); }
    coldef colcls colcls::Div(f32 scale) const requires Integer<T> { return Map(1 / scale, ChannelMulF {}); }
    coldef colcls colcls::AddScalar(T off) const { return Map(off, ChannelAdd {}); }
    coldef colcls colcls::SubScalar(T off) const { return Map(off, ChannelSub {}); }

    coldef colcls& colcls::AddAssign(const IColor& other) { return *this = Add(other); }
    coldef colcls& colcls::SubAssign(const IColor& other) { return *this = Sub(other); }
    coldef colcls& colcls::MulAssign(T scale)            { return *this = Mul(scale); }
    coldef colcls& colcls::MulAssign(f32 scale) requires Integer<T> { return *this = Mul(scale); }
    coldef colcls& colcls::DivAssign(T scale)            { return *this = Div(scale); }
    coldef colcls& colcls::DivAssign(f32 scale) requires Integer<T> { return *this = Div(scale); }
    coldef colcls& colcls::AddScalarAssign(T off)        { return *this = AddScalar(off); }
    coldef colcls& colcls::SubScalarAssign(T off)        { return *this = SubScalar(off); }

    coldef colcls colcls::Inverted() const { return MapRGB(0, ChannelInv {}, AlphaOrFull()); }
    coldef colcls colcls::Lerp(const IColor& other, f32 t) const { return BinaryMap(other, ChannelLerp { t, 1 - t }); }
    coldef colcls colcls::Lerp(const IColor& other, int p, int q) const {
        if constexpr (Integer<T>) return BinaryMap(other, ChannelLerpFraction { p, q - p, q });
        else return Lerp(other, (f32)p / (f32)q);
    }

    coldef colcls& colcls::LerpTowards(const IColor& other, f32 t) {
        return *this = BinaryMap(other, ChannelLerp { t, 1 - t });
    }
    coldef colcls colcls::Blend(const IColor& top) requires HasAlpha {
        if constexpr (Floating<T>)
            return BinaryMapRGB(top, ChannelLerp { top.a, 1 - top.a }, 1 - (1 - a) * (1 - top.a));
        else return BinaryMapRGB(top, ChannelLerpFraction { top.a, (u8)~top.a, 255 }, 255 - (255 - a) * (255 - top.a) / 255);
    }
    coldef colcls colcls::LogBlend(const IColor& other, f32 t) const {
        return BinaryMap(other, ChannelLogBlend { t, 1 - t });
    }
    coldef colcls colcls::LogBlend(const IColor& other, int p, int q) const {
        if constexpr (Integer<T>) return BinaryMap(other, ChannelLogBlendFraction { p, q - p, q });
        else return LogBlend(other, (f32)p / (f32)q);
    }
    coldef colcls colcls::AdjustShade(int brightOff) const requires Integer<T> {
        return Map(brightOff, ChannelAdjust {});
    }
    coldef colcls colcls::AdjustShade(f32 brightOff) const requires Floating<T> {
        return Map(brightOff, ChannelAdjust {});
    }
    coldef colcls colcls::Product(const IColor& other) const {
        return BinaryMap(other, ChannelMul {});
    }
    coldef colcls colcls::Screen (const IColor& other) const {
        return BinaryMap(other, ChannelScreen {});
    }

    coldef colcls colcls::Over(const IColor& other) const {
        if constexpr (HasAlpha) {
            const float alpha = AlphaAs<float>(), premulA = other.AlphaAs<float>() * (1 - a);
            return BinaryMapRGB(other, ChannelLerp { alpha, premulA }, alpha + premulA);
        } else return *this;
    }
    coldef IColor<T, false> colcls::MulAlpha() const {
        constexpr auto mul = ChannelMul {};
        const T alpha = AlphaOrFull();
        return { mul(r, alpha), mul(g, alpha), mul(b, alpha) };
    }
    coldef f32 colcls::Luminance() const {
        return 0.2126f * r + 0.7152f * g + 0.0722f * b;
    }

    coldef colcls colcls::FromBytes(u8 r, u8 g, u8 b, u8 a) {
        return { ByteConv<T>(r),    ByteConv<T>(g),    ByteConv<T>(b),    ByteConv<T>(a)    };
    }
    coldef colcls colcls::FromIntCode(u32 rgb, u8 a) {
        return FromBytes((u8)(rgb >> 16), (u8)(rgb >> 8), (u8)rgb, a);
    }
    coldef colcls colcls::FromIntWithAlpha(u32 rgba) {
        return FromBytes((u8)(rgba >> 24), (u8)(rgba >> 16), (u8)(rgba >> 8), (u8)rgba);
    }
    coldef colcls colcls::FromIntLittleCode(u32 bgr, u8 a) {
        return FromBytes((u8)bgr, (u8)(bgr >> 8), (u8)(bgr >> 16), a);
    }
    coldef colcls colcls::FromIntLittleWithAlpha(u32 abgr) {
        return FromBytes((u8)abgr, (u8)(abgr >> 8), (u8)(abgr >> 16), (u8)(abgr >> 24));
    }
    coldef colcls colcls::FromFloats(f32 r, f32 g, f32 b, f32 a) {
        return { ChannelConv<T>(r), ChannelConv<T>(g), ChannelConv<T>(b), ChannelConv<T>(a) };
    }

    coldef Option<colcls> colcls::FromHex(Str hex) {
        if (hex.StartsWith('#')) hex.Advance(1);
        switch (hex.Length()) {
            case 3: {
                u32 bbggrr = (Memory::ReadU32(hex.Data()) & 0xFFFFFF) | 0x30000000;
                if (!Text::NumberConversion::AreAllHexDigits4(bbggrr)) return nullptr;
                bbggrr = Text::NumberConversion::ConvertHexDigits4(bbggrr);
                bbggrr *= 17;
                return FromIntLittleCode(bbggrr);
            }
            case 4: {
                u32 aabbggrr = Memory::ReadU32(hex.Data());
                if (!Text::NumberConversion::AreAllHexDigits4(aabbggrr)) return nullptr;
                aabbggrr = Text::NumberConversion::ConvertHexDigits4(aabbggrr);
                aabbggrr *= 17;
                return FromIntLittleWithAlpha(aabbggrr);
            }
            case 6: {
                u32 gr = Memory::ReadU32(hex.Data());
                u32 b  = (Memory::ReadU32(hex.Data() + 4) & 0xFFFF )| 0x30300000;
                if (!Text::NumberConversion::AreAllHexDigits4(gr) ||
                    !Text::NumberConversion::AreAllHexDigits4(b)) return nullptr;

                gr = Text::NumberConversion::ConvertHexDigits4(gr);
                b  = Text::NumberConversion::ConvertHexDigits4(b);
                gr += gr << 12;
                gr &= 0xFF00FF00;
                gr = (gr >> 8) + (gr >> 16);
                gr &= 0xFFFF;
                b  += b << 12;
                b  &= 0xFF00;
                return FromIntLittleCode(gr | (b << 8));
            }
            case 8: {
                u64 aabbggrr = Memory::ReadU64(hex.Data());
                if (!Text::NumberConversion::AreAllHexDigits4((u32)aabbggrr) ||
                    !Text::NumberConversion::AreAllHexDigits4(aabbggrr >> 32)) return nullptr;
                aabbggrr &= 0x4F4F4F4F;
                const u64 isLetterChar = aabbggrr & 0x40404040;
                aabbggrr = (isLetterChar >> 6) * 9 + (aabbggrr ^ isLetterChar);

                aabbggrr += aabbggrr << 12;
                aabbggrr &= 0xFF00FF00FF00FF00;
                aabbggrr += aabbggrr << 8;
                aabbggrr &= 0xFFFF0000FFFF0000;
                aabbggrr += aabbggrr << 16;

                return FromIntLittleWithAlpha(aabbggrr >> 32);
            }
            default: return nullptr;
        }
    }

    coldef u32 colcls::GetIntCode() const {
        if constexpr (Integer<T>) {
            return Memory::ReadU32Big(&r) >> (!HasAlpha * 8);
        } else {
            const bv4 rgba = AsRGBAVec();
            return Memory::ReadU32Big(&rgba.x) >> (!HasAlpha * 8);
        }
    }
    coldef String colcls::GetHexCode() const {
        char buf[Dim * 2];
        u32 icode = GetIntCode();
        icode |= icode << 16;
        icode &= 0x00FF00FF;
        icode |= icode << 8;
        icode &= 0x0F0F0F0F;
        icode |= 0x30303030;
        Memory::WriteU32Big(icode, buf);
        return Str::Slice(buf, Dim * 2);
    }
    coldef bool colcls::LooseEq(const IColor& other) const {
        if constexpr (Integer<T>) { return *this == other; }
        else {
            static constexpr f32 THRESHOLD = 1 / 255.0f;
            if constexpr (HasAlpha) if (std::abs(a - other.a) >= THRESHOLD) return false;
            return std::abs(r - other.r) < THRESHOLD &&
                   std::abs(g - other.g) < THRESHOLD &&
                   std::abs(b - other.b) < THRESHOLD;
        }
    }

    coldef colcls colcls::Random(RandomGenerator& rand) {
        return IColor::FromHSV(rand.Get(0.0f, 1.0f), rand.Get(0.4f, 0.6f), 0.95f);
    }
    coldef colcls colcls::RandomPure(RandomGenerator& rand) {
        return IColor::FromIntCode(rand.GetRaw() & 0xFFFFFF);
    }

    template struct IColor<u8,  false>;
    template struct IColor<f32, false>;
    template struct IColor<u8,  true>;
    template struct IColor<f32, true>;

    uColor3 operator ""_rgb  (usize x) { return uColor3::FromIntCode((u32)x); }
    uColor  operator ""_rgba (usize x) { return uColor ::FromIntCode((u32)x); }
    fColor3 operator ""_rgbf (usize x) { return fColor3::FromIntCode((u32)x); }
    fColor  operator ""_rgbaf(usize x) { return fColor ::FromIntCode((u32)x); }
}
