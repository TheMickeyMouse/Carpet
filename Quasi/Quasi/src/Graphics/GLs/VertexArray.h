#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Quasi::Graphics {
    class VertexArray : public GLObject<VertexArray> {
        explicit VertexArray(GraphicsID id);
    public:
        VertexArray() = default;
        static VertexArray New();
        static void DestroyObject(GraphicsID id);
        static void BindObject(GraphicsID id);
        static void UnbindObject();

        void AddBuffer(const VertexBufferLayout& layout);
        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

        friend class GraphicsDevice;
    };
}
