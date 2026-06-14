#pragma once
#include "Func.h"

namespace Quasi {
    template <class T> struct OptRef;
    template <class T> struct Option;

    template <class T> struct Span;
    struct Str;

    namespace Options {
        template <class T> Option<RemQual<T>> Some(T&&);
    }

    /*
     * An interface that describes nullability.
     * Must implement:
     * bool HasValue() const;
     * const? T& Unwrap() const?;
     * void PretendHasValue();
     * void SetNull();
     * static Super None();
     * static Super Some(T&&);
     */
    template <class T, class Super>
    struct INullable {
        using SomeType = T;
        using V = RemQual<T>;
        static constexpr bool USE_RREF = DifferentTo<const T&, T&&>;
        friend Super;

    protected:
        Super& super() { return *static_cast<Super*>(this); }
        const Super& super() const { return *static_cast<const Super*>(this); }

        T&       UnwrapImpl() = delete;
        const T& UnwrapImpl() const = delete;
        bool HasValueImpl() const = delete;
        void SetNullImpl() = delete;
        void SetImpl(const T& value) = delete;
        void SetImpl(T&& value) requires USE_RREF = delete;
        static Super NoneImpl() = delete;
        static Super SomeImpl(const T&) = delete;
        static Super SomeImpl(T&&) requires USE_RREF = delete;
    public:
        bool HasValue() const { return super().HasValueImpl(); }
        bool IsNull() const { return !HasValue(); }
        explicit operator bool() const { return HasValue(); }
        explicit operator bool() { return HasValue(); }

        void SetNull() { super().SetNull(); }
        void Set(const T& value)              { super().SetImpl(value); }
        void Set(T&& value) requires USE_RREF { super().SetImpl(std::move(value)); }

        // checks if self has value AND the inner value satisfies pred
        bool HasValueAnd(Fn<bool, const T&> auto&& pred) const { return HasValue() && pred(Unwrap()); }
        // checks if self is null OR the inner value satisfies pred
        bool IsNullOr   (Fn<bool, const T&> auto&& pred) const { return IsNull() || pred(Unwrap()); }

        T& Unwrap() { return super().UnwrapImpl(); }
        T& operator*() { return Unwrap(); }
        V* operator->() { return &Unwrap(); }
        const T& Unwrap() const { return super().UnwrapImpl(); }
        const T& operator*() const { return Unwrap(); }
        const V* operator->() const { return &Unwrap(); }

        OptRef<T>       AsRef()          { return HasValue() ? Unwrap() : OptRef<T>::None(); }
        Span<T>         AsSpan()         { return HasValue() ? Span<T>::Only(Unwrap()) : Span<T>::Empty(); }
        Option<T>       AsOption() const { return HasValue() ? Option<T>::Some(Unwrap()) : nullptr; }
        OptRef<const T> AsRef()    const { return HasValue() ? SomeRef(Unwrap()) : nullptr; }
        Span<const T>   AsSpan()   const { return HasValue() ? Span<const T>::Only(Unwrap()) : Span<const T>::Empty(); }

        T UnwrapOr(const T& otherwise) const              { return HasValue() ? Unwrap() : otherwise; }
        T UnwrapOr(T&& otherwise) const requires USE_RREF { return HasValue() ? Unwrap() : std::move(otherwise); }
        T UnwrapOrElse(Fn<T> auto&& otherwise) const { return HasValue() ? Unwrap() : otherwise(); }
        Super Or(const Super& otherwise) const { return HasValue() ? *this : otherwise; }
        Super Or(Super&& otherwise)      const { return HasValue() ? *this : std::move(otherwise); }
        Super OrElse(Fn<Super> auto&& otherwise) const { return HasValue() ? *this : otherwise(); }

        // behaves like pythonic and
        Super And(const Super& onlyif) const { return HasValue() ? onlyif            : None(); }
        Super And(Super&& onlyif)      const { return HasValue() ? std::move(onlyif) : None(); }
        auto  AndThen(FnArgs<T> auto&& onlyif) const { return HasValue() ? onlyif(Unwrap()) : nullptr; }

        Super Xor(const Super& extra) const { return HasValue() ^ extra.HasValue() ? (HasValue() ? *this : extra) : None(); }
        Super Xor(Super&& extra)      const { return HasValue() ^ extra.HasValue() ? (HasValue() ? *this : std::move(extra)) : None(); }

        auto Map(auto&& map) const { return HasValue() ? Options::Some(map(Unwrap())) : nullptr; }
        auto MapOr(auto&& map, auto&& otherwise) const { return HasValue() ? map(Unwrap()) : std::forward<decltype(otherwise)>(otherwise); }
        auto MapOrElse(auto&& map, auto&& otherwise) const { return HasValue() ? map(Unwrap()) : otherwise(); }

        Super& Inspect(Fn<void, T&> auto&& inspect) { if (HasValue()) inspect(Unwrap()); return *this; }
        const Super& Inspect(Fn<void, const T&> auto&& inspect) const { if (HasValue()) inspect(Unwrap()); return *this; }

        Super Filter(Fn<bool, T> auto&& pred) const { return this->HasValue() && pred(this->Unwrap()) ? *this : super().NoneImpl(); }

        T& Insert(const T& value)              { Set(value);            return Unwrap(); }
        T& Insert(T&& value) requires USE_RREF { Set(std::move(value)); return Unwrap(); }
        T& GetOrInsert(const T& value)              { if (IsNull()) Insert(value);            return Unwrap(); }
        T& GetOrInsert(T&& value) requires USE_RREF { if (IsNull()) Insert(std::move(value)); return Unwrap(); }
        T& GetOrInsert(Fn<T> auto&& gen)            { if (IsNull()) Insert(gen());            return Unwrap(); }

        Super Take()   { Super out; std::swap(super(), out); return out; }
        Super TakeIf(Fn<bool, T&> auto&& pred) { if (HasValue() && pred(Unwrap())) return Take(); return None(); }

        Super Replace(const T& value)              { Super out = Take(); Set(value); return out; }
        Super Replace(T&& value) requires USE_RREF { Super out = Take(); Set(std::move(value)); return out; }

        // TODO: T::View AsView() requires Viewable<T>;
        // TODO: OptionIter AsIter();
        // TODO: Option<Tuple<T, U>> Zip<U>(Option<U> extra) const;
        // TODO: Option<R> ZipWith<U, F, R>(Option<U> extra, F&& zipper) const;
        // TODO: Tuple<Option<A>, Option<B>> Unzip() const requires T is Tuple<A, B>;
        // TODO: Option<I> Flatten() const requires T is Option<I>;

        T& Assert();
        T& Assert(Str msg);
        T& Assert(auto&& assertfn);
        const T& Assert() const;
        const T& Assert(Str msg) const;
        const T& Assert(auto&& assertfn) const;

        static Super None() { return Super::NoneImpl(); }
        static Super Some(const T& t) { return Super::SomeImpl(t); }
        static Super Some(T&& t) requires USE_RREF { return Super::SomeImpl(std::move(t)); }

        bool operator==(const INullable&) const = default;
    };

    template <class T>
    struct Option : INullable<T, Option<T>> {
        friend INullable<T, Option>;
    private:
        T value;
        bool isSome = true;
    public:
        Option() : Option(nullptr) {}
        Option(Nullptr) : isSome(false) {}
        Option(const T& value) : value(value) {}
        Option(T&& value) : value(std::move(value)) {}

    protected:
        static Option SomeImpl(const T& value) { return { value }; }
        static Option SomeImpl(T&& value) { return { std::move(value) }; }
        static Option NoneImpl() { return { nullptr }; }

        bool HasValueImpl() const { return isSome; }
        T& UnwrapImpl() { return value; }
        const T& UnwrapImpl() const { return value; }

        void SetNullImpl() { isSome = false; }
        void SetImpl(const T& v) { isSome = true; value = v; }
        void SetImpl(T&& v)      { isSome = true; value = std::move(v); }
    public:
        bool operator==(const Option&) const = default;
        bool operator==(const T& other) const { return isSome && value == other; }

        Hashing::Hash GetHashCode() const {
            return isSome ? Hashing::HashObject(value) : Hashing::EmptyHash();
        }
    };

    struct OptionUsize : INullable<usize, OptionUsize> {
        friend INullable;
    private:
        usize value = -1;
    public:
        OptionUsize() = default;
        OptionUsize(Nullptr) : OptionUsize() {}
        OptionUsize(usize value) : value(value) {}
        OptionUsize(ConvTo<usize> auto value) : value(value) {}
        OptionUsize(Option<usize> optval) : value(optval.UnwrapOr(-1)) {}
    protected:
        static OptionUsize SomeImpl(usize value) { return { value }; }
        static OptionUsize NoneImpl() { return { nullptr }; }

        bool HasValueImpl() const { return value != -1; }
        usize& UnwrapImpl() { return value; }
        const usize& UnwrapImpl() const { return value; }

        void SetNullImpl()    { value = -1; }
        void SetImpl(usize v) { value = v; }
    public:
        bool operator==(const OptionUsize&) const = default;
        bool operator==(usize v) const { return value == v; }

        Hashing::Hash GetHashCode() const { return Hashing::HashInt(value); }
    };

    namespace Options {
        template <class T>
        Option<RemQual<T>> Some(T&& value) {
            return Option<RemQual<T>> { std::forward<T>(value) };
        }
    }
}