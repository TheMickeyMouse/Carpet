#pragma once
#include "Numeric.h"

namespace Quasi {
    template <class T> struct Span;
}

namespace Quasi::Hashing {
    enum Hash : usize {};

    inline Hash EmptyHash() { return Hash {}; }
    Hash  AsHash(usize x);
    usize AsIndex(Hash h);

    Hash HashInt(usize x);
    Hash HashBytes(Span<const byte> bytes);
    Hash HashCombine(Hash a, Hash b);

    template <class T> struct Hasher {
        Hash operator()(const T& value) const { return value.GetHashCode(); }
    };

    template <Integer I> struct Hasher<I> {
        Hash operator()(I i) const { return HashInt((usize)i); }
    };

    template <> struct Hasher<void*> {
        Hash operator()(void* ptr) const { return HashInt(reinterpret_cast<usize>(ptr)); }
    };
    template <class T> struct Hasher<T*> : Hasher<void*> {};

    template <class T> Hash HashObject(const T& obj) {
        return Hasher<T> {} (obj);
    }

    struct DefaultHasher {
        Hash operator()(const auto& x) const { return HashObject(x); }
    };
}