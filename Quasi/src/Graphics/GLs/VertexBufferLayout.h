#pragma once

#include "GLTypeID.h"
#include "Utils/Math/Vector.h"
#include "Utils/Math/Color.h"
#include "Utils/Vec.h"
#include "Utils/Type.h"

namespace Quasi::Graphics {
    struct VertexBufferComponent {
        TID::E type;
        u32 count = 0, width = 0;
        bool norm = false, integer = false;

        template <class T> static VertexBufferComponent Type() {
            if constexpr (Floating<T>) return { TID::Of<T>(), 1, sizeof(T) };
            if constexpr (Integer<T>)  return { TID::Of<T>(), 1, sizeof(T), false, true };
            if constexpr (requires (T x) { { Math::Vector { x } } -> SameAs<T>; })
                return { TID::Of<typename T::Elm>(), T::Dim, sizeof(T) };
            if constexpr (requires (T x) { { Math::IColor { x } } -> SameAs<T>; })
                return { TID::Of<typename T::Elm>(), T::Dim, sizeof(T), true, false };
            return {};
        }
    };
    
    class VertexBufferLayout {
    private:
        Vec<VertexBufferComponent> components;
        u32 stride = 0;
    public:
        VertexBufferLayout() = default;
        VertexBufferLayout(IList<VertexBufferComponent> comps);

        template <class... Ts> static VertexBufferLayout FromTypes() {
            return { VertexBufferComponent::Type<Ts>()... };
        }

        template <class T> void Push(u32 count, bool normalized = false, bool integral = false);
        void Push(VertexBufferComponent comp);
        void PushLayout(const VertexBufferLayout& layout);

        const Vec<VertexBufferComponent>& GetComponents() const { return components; }
        u32 GetStride() const { return stride; }
    };

    template <class T>
    void VertexBufferLayout::Push(u32 count, bool normalized, bool integral) {
        TID::E type = TID::Of<T>();
        components.Push({ type, count, normalized, integral });
        stride += count * TID::TSIZE[type - TID::BEGIN];
    }
}
