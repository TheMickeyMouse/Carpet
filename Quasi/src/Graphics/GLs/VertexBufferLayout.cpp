#include "VertexBufferLayout.h"

#include "Utils/Vec.h"

namespace Quasi::Graphics {
    VertexBufferLayout::VertexBufferLayout(IList<VertexBufferComponent> comps) {
        components.Reserve(comps.size());
        for (const auto& component : comps) Push(component);
    }

    void VertexBufferLayout::Push(VertexBufferComponent comp) {
        components.Push(comp);
        stride += comp.count * TID::TSIZE[comp.type - TID::BEGIN];
    }

    void VertexBufferLayout::PushLayout(const VertexBufferLayout& layout) {
        for (const auto& component : layout.GetComponents()) Push(component);
    }
}
