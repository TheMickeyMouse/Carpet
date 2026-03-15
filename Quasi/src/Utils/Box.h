#pragma once
#include <cstdlib>

#include "Memory.h"
#include "Ref.h"

namespace Quasi {
    template <class T, class Super>
    struct IResource {
        using Resource = T;

        IResource() = default;
        IResource(Nullptr) : IResource() {}
        IResource(const IResource&) = delete;
        IResource& operator=(const IResource&) = delete;
        IResource(IResource&&) noexcept = default;
        IResource& operator=(IResource&&) noexcept = default;

        ~IResource() { Close(); }
    protected:
        Super& super() { return *static_cast<Super*>(this); }
        const Super& super() const { return *static_cast<const Super*>(this); }

        void CloseImpl() = delete;
        const T& GetImpl() const = delete;
        T& GetMutImpl() = delete;
        void TransferImpl(Super& dst) = delete;

        void MoveConstructOp(Super& sup) { sup.Transfer(super()); } // c++ doesnt like inheriting move operations so here ya go
        void MoveAssignOp(Super& sup) { Close(); sup.Transfer(super()); }
    public:
        void Close() { return super().CloseImpl(); }

        const T& Get() const { return super().GetImpl(); }
        T& Get()    { return super().GetMutImpl(); }
        T& GetMut() { return super().GetMutImpl(); }

        void Transfer(Super& dst) { return std::move(super()).TransferImpl(dst); }

        const T& operator*() const { return Get(); }
        T& operator*() { return GetMut(); }
        const T* operator->() const { return &Get(); }
        T* operator->() { return &GetMut(); }
    };

    template <class T> struct ArrayBox;

    struct GlobalDelete {
        void operator()(auto* ptr) const { Memory::Free(ptr); }
    };

    template <class T, class A = GlobalDelete>
    struct Box : IResource<T, Box<T, A>> {
        friend IResource<T, Box>;
    private:
        T* data = nullptr;
        [[no_unique_address]] A allocator = {};
        Box(T* data, A alloc = {}) : data(data), allocator(std::move(alloc)) {}
    public:
        Box() : data(nullptr) {}
        Box(Nullptr) : data(nullptr) {}
        Box(Box&& box) noexcept { this->MoveConstructOp(box); }
        template <Extends<T> Derived> Box(Box<Derived>&& box) : data(box.Release()), allocator(std::move(box.allocator)) {}
        Box& operator=(Box&& box) noexcept { this->MoveAssignOp(box); return *this; }

        static Box New        (T value)                 { return { Memory::Allocate<T>(std::move(value)) }; }
        static Box NewUninit  ()                        { return { Memory::AllocateUninit<T>() }; }
        static Box Build      (auto&&... args)          { return { Memory::Allocate<T>((decltype(args))args...) }; }
        static Box NewIn      (A alloc, T value)        { return { Memory::Allocate<T>(std::move(value)),        std::move(alloc) }; }
        static Box NewUninitIn(A alloc)                 { return { Memory::AllocateUninit<T>(),                  std::move(alloc) }; }
        static Box BuildIn    (A alloc, auto&&... args) { return { Memory::Allocate<T>((decltype(args))args...), std::move(alloc) }; }
        static Box Own(Ref<T> data) { return { data.Address() }; }
        static Box Own(T* data)     { return { data }; }
        static Box OwnIn(A alloc, Ref<T> data) { return { data.Address(), std::move(alloc) }; }
        static Box OwnIn(A alloc, T* data)     { return { data, std::move(alloc) }; }
        static Box Empty()          { return {}; }
        static Box EmptyIn(A alloc) { return { nullptr, std::move(alloc)}; }
    protected:
        void CloseImpl() { allocator(data); data = nullptr; }

        const T& GetImpl() const { return *data; }
        T& GetMutImpl() { return *data; }

        void TransferImpl(Box& dst) { dst.data = data; dst.allocator = std::move(allocator); data = nullptr; }
    public:
        T Extract() { T out = std::move(*data); CloseImpl(); return out; }
        [[nodiscard]] T* Release() { T* out = data; data = nullptr; return out; }
        [[nodiscard]] Ref<T> Leak() { return Ref<T>::Deref(Release()); }

        Ref<const T> AsRef() const { return Ref<const T>::Deref(data); }
        Ref<T> AsRef() { return Ref<T>::Deref(data); }
        bool RefEquals(Ref<const T> other) const { return data == other.Address(); }

        const T* Data() const { return data; }
        T* Data() { return data; }
        T* DataMut() { return data; }

        const A& Allocator() const { return allocator; }
        A& AllocatorMut() { return allocator; }

        void Write(T value) { Memory::ConstructMoveAt(std::move(value)); }
        void Replace(T* val) { CloseImpl(); data = val; }
        T*   Take   (T* val) { T* out = Release(); data = val; return out; }
        void Swap(Box& other) { std::swap(data, other.data); std::swap(allocator, other.allocator); }

        Box Clone() const { return Box::NewIn(allocator, *data); }

        template <Extends<T> Derived> Box<Derived> Downcast() {
            Derived* dyn = Memory::DynCastPtr<Derived>(data);
            if (dyn) {
                (void)Release();
                return Box<Derived>::Own(dyn);
            } else return nullptr;
        }

        template <BaseOf<T> Base> Box<Base> Upcast() {
            Base* dyn = Memory::DynCastPtr<Base>(data);
            if (dyn) {
                (void)Release();
                return Box<Base>::Own(dyn);
            } else return nullptr;
        }

        template <class U>
        OptRef<const U> As() const { return OptRef<const U>::Deref(dynamic_cast<const U*>(data)); }
        template <class U> requires IsMut<T>
        OptRef<U> As() { return OptRef<U>::Deref(dynamic_cast<U*>(data)); }

        Span<const T> AsSpan() const;
        Span<T> AsSpanMut();
        ArrayBox<T> IntoArrayBox();

        [[nodiscard]] bool IsNull()    const { return data == nullptr; }
        [[nodiscard]] bool OwnsValue() const { return data != nullptr; }

        explicit operator bool() const { return data != nullptr; }

        template <class _T, class _A> friend struct Box;
    };

    namespace Boxs {
        template <class T>
        Box<T> New(T val) { return Box<T>::New(std::move(val)); }
    }

    struct GlobalArrayDelete {
        void operator()(auto* ptr) const { Memory::FreeArray(ptr); }
    };
    template <class T> using BufferBox = Box<T, GlobalArrayDelete>;

    struct MallocFreeDelete {
        void operator()(auto* ptr) const { std::free(ptr); }
    };
    template <class T> using CBox = Box<T, MallocFreeDelete>;
}
