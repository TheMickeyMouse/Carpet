#pragma once

#include "GLObject.h"
#include "../Triplet.h"
#include "Utils/Span.h"

namespace Quasi::Graphics {
    class IndexBuffer : public GLObject<IndexBuffer> {
    private:
        u32 bufferSize = 0;
        u32 dataOffset = 0;

        explicit IndexBuffer(GraphicsID id, u32 size);
    public:
        IndexBuffer() = default;
        static IndexBuffer New(u32 size);
        static void DestroyObject(GraphicsID id);
        static void BindObject(GraphicsID id);
        static void UnbindObject();

        void SetData(Span<const u32> data, u32 dOffset = 0);
        void SetData(Span<const Triplet> data, u32 dOffset = 0) { SetData(data.Transmute<u32>(), dOffset); }

        void ClearData(); // this doesnt actually clear the dataz, just makes it not

        void AddData(Span<const u32> data);
        void AddData(Span<const Triplet> data) { AddData(data.Transmute<u32>()); }

        u32 GetLength() const { return bufferSize; }
        u32 GetUsedLength() const { return dataOffset; }

        friend class GraphicsDevice;
    };
}
