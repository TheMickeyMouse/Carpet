#pragma once
#include "Matrix.h"

namespace Quasi::Math {
    template <class T>
    struct Complex {
        using fT = Common<T, float>;
        T re = 0, im = 0;

        Complex() = default;
        Complex(T r) : re(r) {}
        Complex(T r, T i) : re((T)r), im((T)i) {}

        Vec2<T> AsVec2D() const { return { re, im }; }
        static Complex FromVec2D(const Vec2<T>& ri) { return { ri.x, ri.y }; }
        inline static const Complex i = { 0, 1 };

        fT Realf() const { return (fT)re; }
        fT Imagf() const { return (fT)im; }

        T  LenSq() const { return re * re + im * im; }
        fT Len() const { return std::sqrt(LenSq()); }
        fT Abs() const { return Len(); }
        T  DistSq(const Complex& z) const { return (*this - z).LenSq(); }
        fT Dist(const Complex& z) const { return (*this - z).Len(); }
        Complex<fT> Norm() const { return *this / Len(); }
        Tuple<Complex<fT>, fT> NormAndLen() const { const fT len = Len(); return { *this / Len(), len }; }

        Radians Angle() const { return Math::Atan2(Imagf(), Realf()); }
        Radians AngleBetween(const Complex& other) const {
            return Trig::Arccos((re * other.re + im * other.im) / std::sqrt(Abs() * other.Abs()));
        }

        static Complex Exp(const Complex& z) requires Floating<T> {
            const fT r = std::exp(z.re);
            return { r * std::cos(z.im), r * std::sin(z.im) };
        }
        static Complex ExpImag(T imag) requires Floating<T> { return { std::cos(imag), std::sin(imag) }; }
        Complex Exp() const requires Floating<T> { return ExpImag(Imagf()) * std::exp(Realf()); }
        Complex Log() const requires Floating<T> { return { std::log(LenSq()) * 0.5f, *Angle() }; }

        // sqrt has positive real values
        Complex<fT> Sqrt() const requires Floating<T> {
            const fT r = Abs(), im2 = HALF_ROOT_2 * std::sqrt(r - re);
            return { HALF_ROOT_2 * std::sqrt(r + re), im < 0 ? -im2 : im2 };
        }
        // sqrt has positive real values
        Complex<fT> UnitSqrt() const requires Floating<T> {
            const fT im2 = HALF_ROOT_2 * std::sqrt(1 - re);
            return { HALF_ROOT_2 * std::sqrt(1 + re), im < 0 ? -im2 : im2 };
        }
        // uppersqrt has positive imaginary values
        Complex<fT> UpperSqrt() const requires Floating<T> {
            const fT r = Abs(), re2 = HALF_ROOT_2 * std::sqrt(r + re);
            return { im < 0 ? -re2 : re2, HALF_ROOT_2 * std::sqrt(r - re) };
        }
        // uppersqrt has positive imaginary values
        Complex<fT> UnitUpperSqrt() const requires Floating<T> {
            const fT re2 = HALF_ROOT_2 * std::sqrt(1 + re);
            return { im < 0 ? -re2 : re2, HALF_ROOT_2 * std::sqrt(1 - re) };
        }
        Complex<fT> Pow(f32 p) const requires Floating<T> {
            return ExpImag(*Angle() * p) * std::pow(Abs(), p);
        }
        Complex<fT> PowImag(f32 imag) const requires Floating<T> {
            return ExpImag(std::log(LenSq()) * 0.5f * imag) * std::exp(-*Angle() * imag);
        }
        Complex<fT> Pow(Complex p) const requires Floating<T> {
            return (Log() * p).Exp();
        }
        Complex Squared() const { return { re * re - im * im, 2 * re * im }; }
        Complex Cubed()   const {
            const T r2 = re * re, i2 = im * im;
            return { re * (r2 - 3 * i2), im * (3 * r2 - i2) };
        }

        Complex Conj() const { return { re, -im }; }
        Complex<fT> Inverse() const { const fT invLenSq = (fT)1 / LenSq(); return { Realf() * invLenSq, -Imagf() * invLenSq }; }

        Matrix2x2 AsMatrixLinear() const {
            return {{ (float)re, -(float)im,
                      (float)im,  (float)re }};
        }
        Matrix2D AsMatrix() const {
            return {{ (float)re, -(float)im, 0,
                      (float)im,  (float)re, 0,
                      0,          0,         1 }};
        }
        // v2<T> rotate(const v2<T>& v)    const { return { v.x * re - v.y * im, v.x * im + v.y * re }; }
        // v2<T> invrotate(const v2<T>& v) const { return { v.x * re + v.y * im, v.y * re - v.x * im }; }

        Complex MulI()    const { return { -im, re }; }
        Complex MulNegI() const { return { im, -re }; }

        Complex<fT> Lerp(const Complex& z, fT t) const {
            return { Realf() + (z.Realf() - Realf()) * t, Imagf() + (z.Imagf() - Imagf()) * t };
        }
        Complex<fT> Slerp(const Complex& z, fT t) const {
            const Radians theta = AngleBetween(z);
            const fT inv = 1 / Sin(theta);
            const fT p = Trig::Sin(theta * (1 - t)) * inv, q = Trig::Sin(theta * t) * inv;
            return (*this) * p + z * q;
        }

        Complex operator+() const { return *this; }
        Complex operator-() const { return { -re, -im }; }
        Complex operator+(const Complex& z) const { return { re + z.re, im + z.im }; }
        Complex operator-(const Complex& z) const { return { re - z.re, im - z.im }; }
        Complex operator*(const Complex& z) const { return { re * z.re - im * z.im, re * z.im + im * z.re }; }
        Complex<fT> operator/(const Complex& z) const { return (Complex<fT>)*this * z.Inverse(); }
        Complex& operator+=(const Complex& z) { re += z.re; im += z.im; return *this; }
        Complex& operator-=(const Complex& z) { re -= z.re; im -= z.im; return *this; }
        Complex& operator*=(const Complex& z) { T real = re; re = re * z.re - im * z.im; im = real * z.im + im * z.re; return *this; }
        Complex& operator/=(const Complex& z) { return (*this) *= z.Inverse(); }

        Complex     operator^(fT p)             const requires Floating<T> { return Pow(p); }
        Complex<fT> operator^(const Complex& p) const requires Floating<T> { return Pow(p); }
        Complex&    operator^=(fT p)              requires Floating<T> { return *this = Pow(p); }
        Complex<fT>& operator^=(const Complex& p) requires Floating<T> { return *this = Pow(p); }

        template <class U> operator Complex<U>() const { return { (U)re, (U)im }; }

        // static Complex random_rot(RandomGenerator& rg);
    };

    template <class T> Complex<T> operator+(T x, const Complex<T>& z) { return  z + x; }
    template <class T> Complex<T> operator-(T x, const Complex<T>& z) { return -z + x; }
    template <class T> Complex<T> operator*(T x, const Complex<T>& z) { return  z * x; }
    template <class T> Complex<T> operator/(T x, const Complex<T>& z) requires Floating<T> { return z.Inverse() * x; }
    template <class T> Complex<T> operator^(T x, const Complex<T>& z) requires Floating<T> { return Complex<T>::Exp(std::log(x) * z); }

    // template <class T>
    // typename VectorN<2, T>::float_vec VectorN<2, T>::rotated_by(const Complex<T>& rotation) const {
    //     return rotation.rotate(*this);
    // }
    //
    // template <class T>
    // VectorN<2, T>& VectorN<2, T>::rotate_by(const Complex<T>& rotation) requires traits_float {
    //     return *this = rotation.rotate(*this);
    // }

    using iComplex = Complex<int>;
    using fComplex = Complex<float>;

    inline fComplex operator ""_i(long double f) { return fComplex { 0, (f32)f }; }
    inline iComplex operator ""_i(u64 i) { return iComplex { 0, (i32)i }; }
}

namespace Quasi::Text {
    template <class T>
    struct Formatter<Math::Complex<T>> {
        static usize FormatTo(StringWriter output, const Math::Complex<T>& z, Str) {
            usize n = Text::FormatObjectTo(z.re);
            if (z.im != 0) {
                output.Write(z.im < 0 ? " - " : " + ");
                n += Text::FormatObjectTo(z.im);
                output.Write('i');
                return n + 4;
            }
            return n;
        }
    };
}