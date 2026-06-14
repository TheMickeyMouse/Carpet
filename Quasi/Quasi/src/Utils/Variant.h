#pragma once
#include "Ref.h"
#include "Type.h"

namespace Quasi {
    template <class T, class... Ts> union RawUnion;

    template <class Super>
    struct ITaggedUnion {
    protected:
        Super& super() { return *static_cast<Super*>(this); }
        const Super& super() const { return *static_cast<const Super*>(this); }

        /* should be a RawUnion */ const auto& GetUnionImpl() const = delete;
        /* should be a RawUnion */ auto& GetUnionMutImpl() = delete;

        usize GetTagImpl() const = delete;
        template <class T> static usize TagForImpl() = delete;

        template <class R> R VisitImpl(auto&& visitor) const = delete;
        template <class R> R VisitMutImpl(auto&& visitor) = delete;
    public:
        const auto& AsRawUnion() const { return super().GetUnionImpl(); }
        auto& AsMutRawUnion() { return super().GetUnionMutImpl(); }
        usize GetTag() const { return super().GetTagImpl(); }
        template <class T> static usize TagFor() { return Super::template TagForImpl<T>(); }

        template <class U> U&       AsUnsafe()       { return super().GetUnionMutImpl().template As<U>(); }
        template <class U> const U& AsUnsafe() const { return super().GetUnionImpl().template As<U>(); }
        template <class U> bool Is() const { return GetTag() == TagFor<U>(); }
        template <class U> OptRef<const U> As() const { return Is<U>() ? OptRefs::SomeRef(AsUnsafe<U>()) : nullptr; }
        template <class U> OptRef<U>       As()       { return Is<U>() ? OptRefs::SomeRef(AsUnsafe<U>()) : nullptr; }

        template <class R = void> R Visit(auto&& visitor) const {
            return super().template VisitImpl<R>((decltype(visitor))visitor);
        }
        template <class R = void> R Visit(auto&&... visitors) const {
            return Visit<R>(Combinate::Overload { (decltype(visitors))visitors... });
        }
        template <class R = void> R VisitMut(auto&& visitor) {
            return super().template VisitMutImpl<R>((decltype(visitor))visitor);
        }
        template <class R = void> R VisitMut(auto&&... visitors) {
            return VisitMut<R>(Combinate::Overload { (decltype(visitors))visitors... });
        }
    };

    template <class T, class... Ts> union RawUnion {
        T leaf;
        RawUnion<Ts...> branch;

        RawUnion() {}
        ~RawUnion() {}

        template <class U> void InitWith(U u) {
            if constexpr (SameAs<T, U>) new (&leaf) T(std::move(u));
            else branch.template InitWith<U>(std::move(u));
        }
        template <class U> void DestroyAs() {
            if constexpr (SameAs<T, U>) leaf->~T();
            else branch.template DestroyAs<U>();
        }
        template <class U> U& As() {
            if constexpr (SameAs<T, U>) return leaf;
            else return branch.template As<U>();
        }
        template <class U> const U& As() const {
            if constexpr (SameAs<T, U>) return leaf;
            else return branch.template As<U>();
        }
    };

    template <class T> union RawUnion<T> {
        T leaf;

        RawUnion() {}
        ~RawUnion() {}

        template <SameAs<T>> void InitWith(T u) { new (&leaf) T(std::move(u)); }
        template <SameAs<T>> void DestroyAs()    { leaf->~T(); }
        template <SameAs<T>> const T& As() const { return leaf; }
        template <SameAs<T>> T&       As()       { return leaf; }
    };

    template <class... Ts>
    struct Variant : ITaggedUnion<Variant<Ts...>> {
        friend ITaggedUnion<Variant>;
    private:
        usize tag = 0;
        RawUnion<Ts...> inner;
    protected:
        const RawUnion<Ts...>& GetUnionImpl() const { return inner; }
        RawUnion<Ts...>& GetUnionMutImpl() { return inner; }

        usize GetTagImpl() const { return tag; }
        template <class T> static usize TagForImpl() { return IndexOfType<T, Ts...>(); }

        template <class R = void>
        R VisitImpl(auto&& visitor) const {
            using F = RemRef<decltype(visitor)>;
            static constexpr R(*F_TABLE[])(void*, const void*) = {
                +([] (void* vptr, const void* input) -> R { return (*(F*)vptr)(*(const Ts*)input); })...
            };
            return F_TABLE[tag](&visitor, &inner);
        }
        template <class R = void>
        R VisitMutImpl(auto&& visitor) {
            using F = RemRef<decltype(visitor)>;
            static constexpr R(*F_TABLE[])(void*, void*) = {
                +([] (void* vptr, void* input) -> R { return (*(F*)vptr)(*(Ts*)input); })...
            };
            return F_TABLE[tag](&visitor, &inner);
        }
    public:
        Variant() = delete;
        template <class T> requires DistantTo<T, Variant> Variant(T&& t) : tag(TagForImpl<RemQual<T>>()) { inner.InitWith((T&&)t); }
        Variant(const Variant& v) : tag(v.tag) {
            v.VisitImpl([&] (const auto& x) { inner.InitWith(x); });
        }
        Variant(Variant&& v) noexcept : tag(v.tag) {
            v.VisitMutImpl([&] (auto& x) { inner.InitWith(std::move(x)); });
        }

        Variant& operator=(const Variant& v) {
            this->~Variant();
            new (this) Variant(v);
            return *this;
        }

        Variant& operator=(Variant&& v) noexcept {
            this->~Variant();
            new (this) Variant(std::move(v));
            return *this;
        }

        template <class T>
        Variant& operator=(T t) {
            this->~Variant();
            tag = TagForImpl<T>();
            inner.InitWith(std::move(t));
            return *this;
        }

        ~Variant() { VisitMutImpl(Operators::Destructor {}); }

        template <class T> void Set(T t) { *this = std::move(t); }
    };
}
