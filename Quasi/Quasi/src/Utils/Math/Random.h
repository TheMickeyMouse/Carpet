#pragma once
#include <random>
#include <chrono>

#include "Constants.h"

namespace Quasi::Math {
    // man why doesnt c++ just have a standard random library thats actually easy to use
    struct RandomGenerator {
        inline static std::seed_seq seeder {
            std::random_device {}(),
            (u32)std::chrono::steady_clock::now().time_since_epoch().count()
        };
        std::mt19937 device { GetSeed() };

        template <class T> using IntDistribution   = std::uniform_int_distribution<T>;
        template <class T> using RealDistribution  = std::uniform_real_distribution<T>;
        template <class T> using GaussDistribution = std::normal_distribution<T>;
        using BoolDistribution = std::bernoulli_distribution;

        RandomGenerator() = default;

        static std::seed_seq& GetSeed() { return seeder; }
        void SetSeed(const u32 val) { device.seed(val); }
        template <class Sq> void SetSeed(Sq& newSeeder) { device.seed(newSeeder()); }
        void Reseed() { device.seed(seeder); }

        void Discard(u64 num) { device.discard(num); }
        u32 GetRaw() { return device(); }

        template <Integer I> I Get(I min, I max) { return GetIncl(min, (I)(max - 1)); }
        template <Integer I> I GetIncl(I min, I max) { return IntDistribution<I> { min, max } (device); }

        template <Floating F> F Get(F min = 0, F max = 1) { return RealDistribution<F> { min, max } (device); }

        template <Floating F> F GetLogarithmic(F min = 0, F max = 1)
        { return std::log(Get(std::exp(min), std::exp(max))); }
        template <Floating F> F GetExponential(F min = 0, F max = 1)
        { return std::exp(Get(std::log(min), std::log(max))); }

        template <Floating F> F GetGaussian(F mean, F stddev) { return GaussDistribution<F> { mean, stddev } (device); }

        u8 GetByte(u8 min, u8 max) { return (u8)Get<u16>(min, max); }

        bool GetBool(f32 probability = 0.5f) { return BoolDistribution { probability } (device); }
        bool GetBool(int num, int denom) { return Get(0, denom) >= num; }

        template <class F> auto GetForDistribution(F f) -> decltype(f(0)) { return f(device); }

        template <class T>
        T Choose(IList<T> ilist) { return Choose(Spans::FromIList(ilist)); }

        template <ContinuousAny C>
        CollectionItem<C>&       Choose(C& arr)       { return arr[Get<usize>(0, arr.Length())]; }
        template <ContinuousAny C>
        const CollectionItem<C>& Choose(const C& arr) { return arr[Get<usize>(0, arr.Length())]; }

        template <class T, template <typename> class C = Vec> C<T> Generate(T min, T max, usize size) {
            C arr = C<T>::WithCap(size);
            for (usize i = 0; i < size; ++i) arr.Push(Get(min, max));
            return arr;
        }

        template <class T, usize N> Array<T, N> GenerateArray(T min, T max) {
            Array<T, N> arr;
            for (usize i = 0; i < N; ++i) arr[i] = Get(min, max);
            return arr;
        }

        template <class F, template <typename> class C = Vec>
        auto GenerateWith(F f, usize size) -> C<decltype(f(0))> {
            C arr = C<decltype(f(0))>::WithCap(size);
            for (usize i = 0; i < size; ++i) arr.Push(Get(f));
            return arr;
        }

        template <class F, usize N> auto GenerateArrayWith(F f) -> Array<decltype(f(0)), N> {
            Array<decltype(f(0)), N> arr;
            for (usize i = 0; i < N; ++i) arr[i] = Get(f);
            return arr;
        }
    };

    template <class T, usize N>
    Vector<T, N> IVector<T, N>::Random(RandomGenerator& rand, const Super& min, const Super& max) {
        Super v;
        for (usize i = 0; i < N; ++i) v[i] = rand.Get(min[i], max[i]);
        return v;
    }
    template <class T, usize N>
    Vector<T, N> IVector<T, N>::Random(RandomGenerator& rand) { return Random(rand, 0, 1); }
    template <class T, usize N>
    Vector<T, N> IVector<T, N>::Random(RandomGenerator& rand, const Rect<T, N>& range) {
        return Random(rand, range.min, range.max);
    }
    template <class T, usize N>
    Vector<T, N> IVector<T, N>::RandomOnUnit(RandomGenerator& rand) requires Floating<T> {
        Super v;
        for (usize i = 0; i < N; ++i) v[i] = rand.GetGaussian<T>(0, 1);
        return v.Norm();
    }

    template <class T, usize N>
    Vector<T, N> IVector<T, N>::RandomInUnit(RandomGenerator& rand) requires Floating<T> {
        return RandomOnUnit(rand) * std::pow(rand.Get<T>(), (T)1 / N);
    }
}
