#pragma once
#include "Box.h"
#include "Continuous.h"

namespace Quasi {
    template <class T>
    struct ArrayBox : IResource<Span<T>, ArrayBox<T>>, IContinuous<T, ArrayBox<T>> {
        friend IResource<Span<T>, ArrayBox>;
        friend IContinuous<T, ArrayBox>;
    private:
        T* buf;
        usize size;

        ArrayBox(T* buf, usize size) : buf(buf), size(size) {}
    public:
        ArrayBox() : buf(nullptr), size(0) {}
        ArrayBox(Nullptr) : buf(nullptr), size(0) {}
        using IResource<Span<T>, ArrayBox>::IResource;
        using IResource<Span<T>, ArrayBox>::operator=;

        static ArrayBox Allocate      (usize amt) { return { Memory::AllocateArray<T>(amt), amt }; }
        static ArrayBox AllocateUninit(usize amt) { return { Memory::AllocateArrayUninit<T>(amt), amt }; }
        template <usize N>
        static ArrayBox Build(T (&&arr) [N]) {
            T* buf = Memory::AllocateArrayUninit<T>(N);
            for (usize i = 0; i < N; ++i)
                Memory::ConstructMoveAt(&buf[i], std::move(arr[i]));
            return { buf, N };
        }
        static ArrayBox Own(T* data, usize len) { return { data, len }; }
        static ArrayBox Own(Span<T> data) { return { data.Data(), data.Length() }; }
        static ArrayBox Copy(Span<const T> data) { return data.CollectArrayBox(); }
    protected:
        void CloseImpl() { Memory::Free(buf); buf = nullptr; size = 0; }

        RemRef<T>* DataImpl() { return buf; }
        const RemRef<T>* DataImpl() const { return buf; }
        usize LengthImpl() const { return size; }

        void TransferImpl(ArrayBox& dst) { dst.buf = buf; buf = nullptr; dst.size = size; size = 0; }
    public:
        Span<const T> AsSpan() const { return Span<const T>::Slice(buf, size); }
        Span<T> AsSpanMut() { return Span<T>::Slice(buf, size); }
        Span<const T> Get() const { return AsSpan(); }
        Span<T> GetMut() { return AsSpanMut(); }

        [[nodiscard]] T* Release() { T* out = buf; buf = nullptr; size = 0; return out; }
        [[nodiscard]] Span<T> Leak() { Span<T> out = AsSpanMut(); buf = nullptr; size = 0; return out; }

        void    Write  (Span<T> val) { for (usize i = 0; i < size; ++i) Memory::ConstructMoveAt(&buf[i], std::move(val)); }
        void    Replace(Span<T> val) { CloseImpl(); buf = val.Data(); size = val.Length(); }
        Span<T> Take   (Span<T> val) { Span<T> out = Leak(); buf = val.Data(); size = val.Length(); return out; }
        void    Swap(ArrayBox& other) { std::swap(buf, other.buf); std::swap(size, other.size); }

        ArrayBox Clone() const { return AsSpan().IntoArrayBox(); }

        void CloneFrom(Span<const T> src) { AsSpan().CloneFrom(src); }
        void MoveFrom (Span<T> src)       { AsSpan().MoveFrom(src); }

        [[nodiscard]] bool IsNull()    const { return buf == nullptr; }
        [[nodiscard]] bool OwnsValue() const { return buf != nullptr; }

        Span<const T> operator*() const { return AsSpan(); }
        Span<T> operator*() { return AsSpanMut(); }
        Span<const T>* operator->() const = delete;
        Span<T>* operator->() = delete;

        explicit operator bool() const { return buf != nullptr; }
    };

    template <class T, class A> ArrayBox<T> Box<T, A>::IntoArrayBox() {
        return ArrayBox<T>::Own(Release(), 1);
    }
}
