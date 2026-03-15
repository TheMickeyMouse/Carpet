#pragma once
#include "Memory.h"
#include "Option.h"
#include "Type.h"

namespace Quasi {
    template <class> struct Ref;
    template <class> struct OptRef;

    namespace Hashing { enum Hash : usize; }

    /*
     * An interface that describes ref classes.
     * Must implement:
     * const? T& ValueImpl() const?;
     */
    template <class T, class Super>
    struct IReference {
        using Resource = T;
        friend Super;
    protected:
        Super& super() { return *static_cast<Super*>(this); }
        const Super& super() const { return *static_cast<const Super*>(this); }

        T& ValueImpl() requires IsMut<T> = delete;
        const T& ValueImpl() const = delete;
    public:
        T& Value() requires IsMut<T> { return super().ValueImpl(); }
        const T& Value() const { return super().ValueImpl(); }
        T* Address() requires IsMut<T> { return &Value(); }
        const T* Address() const { return &Value(); }

        operator const T&() const { return Value(); }
        operator T&() { return Value(); }

        T& operator*() requires IsMut<T> { return Value(); }
        const T& operator*() const { return Value(); }
        T* operator->() requires IsMut<T> { return Address(); }
        const T* operator->() const { return Address(); }

        Ref<T> AsRef() requires IsMut<T> { return Ref<T>::Deref(Address()); }
        Ref<const T> AsRef() const { return Ref<const T>::Deref(Address()); }
    };

    template <class T>
    struct Ref : IReference<T, Ref<T>> {
        friend IReference<T, Ref>;

        T* obj;
    private:
        Ref(T* t) : obj(t) {}
    public:
        Ref(T& t) : obj(&t) {}

        using ConstRef = Ref<const T>;

        static Ref Deref(T* t) { return { t }; }

    protected:
        T& ValueImpl() { return *obj; }
        const T& ValueImpl() const { return *obj; }
    public:
        bool Equals(Ref r) const {
            return *r == *obj;
        }
        bool RefEquals(ConstRef r) const { return r.obj == obj; }
        void SetRef(T& r) { obj = &r; }

        bool operator==(ConstRef r) const { return this->Equals(r); }

        Hashing::Hash GetHashCode() const { return Hashing::HashObject(*obj); }

        Ref<RemConst<T>> AsMut() requires IsConst<T> { return { (RemConst<T>*)obj }; }
        Ref<const T> AsConst() const requires IsMut<T> { return { (const T*)obj }; }

        operator ConstRef() const { return AsConst(); }
        explicit operator Ref<RemConst<T>>() { return AsMut(); }
        template <Extends<T> Base> requires DifferentTo<T, Base> operator OptRef<const Base>() const;
        template <Extends<T> Base> requires DifferentTo<T, Base> && IsMut<T> operator OptRef<Base>();

        template <Extends<T> U>
        OptRef<const U> As() const { return dynamic_cast<const U*>(obj); }
        template <Extends<T> U> requires IsMut<T>
        OptRef<U> As() { return dynamic_cast<U*>(obj); }

        template <class Re> Ref<Re> TransmuteAs() { return Memory::TransmutePtr<Re>(obj); }
        template <class Re> Ref<const Re> TransmuteAs() const { return Memory::TransmutePtr<const Re>(obj); }

        template <class U> friend struct Ref;
    };

    template <class T>
    struct OptRef : INullable<T&, OptRef<T>>, IReference<T, OptRef<T>> {
        friend INullable<T&, OptRef>;
        friend IReference<T, OptRef>;
    private:
        T* obj = nullptr;
        OptRef(T* t) : obj(t) {}
    public:
        OptRef() : obj(nullptr) {}
        OptRef(Nullptr) : obj(nullptr) {}
        OptRef(T& t) : obj(&t) {}
        OptRef(Ref<T> t) : obj(t.Address()) {}

        using IReference<T, OptRef>::operator->;
        using IReference<T, OptRef>::operator*;

        using ConstRef = OptRef<const T>;

        static OptRef Deref(T* t) { return { t }; }

    protected:
        static OptRef SomeImpl(const T& value) requires IsConst<T> { return { value }; }
        static OptRef SomeImpl(T& value) { return { value }; }
        static OptRef NoneImpl() { return { nullptr }; }

        T& ValueImpl() { return *obj; }
        const T& ValueImpl() const { return *obj; }

        bool HasValueImpl() const { return obj; }
        T& UnwrapImpl() const { return *obj; }

        void SetNullImpl() { obj = nullptr; }
        void SetImpl(T& v) { obj = &v; }
    public:
        bool Equals(OptRef r) const {
            return this->IsNull() ? r.IsNull() : r.HasValue() && *r == *obj;
        }
        bool RefEquals(OptRef r) const { return r.obj == obj; }
        void SetRef(OptRef r) { obj = r.Address(); }
        void SetNull() { obj = nullptr; }

        bool operator==(ConstRef r) const { return this->Equals(r); }

        Hashing::Hash GetHashCode() const { return obj ? Hashing::HashObject(*obj) : Hashing::EmptyHash(); }

        OptRef<RemConst<T>> AsMut() requires IsConst<T> { return { (RemConst<T>*)obj }; }
        OptRef<const T> AsConst() const requires IsMut<T> { return { (const T*)obj }; }

        operator ConstRef() const { return AsConst(); }
        explicit operator OptRef<RemConst<T>>() { return AsMut(); }
        template <Extends<T> Base> requires DifferentTo<T, Base> operator OptRef<const Base>() const { return obj; }
        template <Extends<T> Base> requires DifferentTo<T, Base> && IsMut<T> operator OptRef<Base>() { return obj; }

        template <Extends<T> U>
        OptRef<const U> As() const { return dynamic_cast<const U*>(obj); }
        template <Extends<T> U> requires IsMut<T>
        OptRef<U> As() { return dynamic_cast<U*>(obj); }

        Option<RemConst<T>> Copied() const { return obj ? Options::Some(*obj) : nullptr; }

        template <class Re> OptRef<Re> TransmuteAs() { return Memory::TransmutePtr<Re>(obj); }
        template <class Re> OptRef<const Re> TransmuteAs() const { return Memory::TransmutePtr<const Re>(obj); }

        template <class U> friend struct OptRef;
    };

    namespace Refs {
        template <class T> Ref<T> Refer(T& val) { return { val }; }
        template <class T> Ref<T> Refer(Ref<T> val) { return val; }
    }

    namespace OptRefs {
        template <class T> OptRef<T> Some(Ref<T> ref) { return { ref }; }
        template <class T> OptRef<T> SomeRef(T& val) { return { val }; }
        template <class T> OptRef<T> DerefPtr(T* val) { return OptRef<T>::Deref(val); }
    }

    template <class T> template <Extends<T> Base> requires DifferentTo<T, Base>
    Ref<T>::operator OptRef<const Base>() const { return OptRefs::DerefPtr(obj); }
    template <class T> template <Extends<T> Base> requires DifferentTo<T, Base> && IsMut<T>
    Ref<T>::operator OptRef<Base>() { return OptRefs::DerefPtr(obj); }
}
