#include "IndexBuffer.h"

#include <algorithm>
#include <vector>
#include <glp.h>

#include "GLDebug.h"

namespace Quasi::Graphics {
    IndexBuffer::IndexBuffer(GraphicsID id, u32 size) : GLObject(id), bufferSize(size) {}

    IndexBuffer IndexBuffer::New(u32 size) {
        GraphicsID id;
        QGLCall$(GL::GenBuffers(1, &id));
        BindObject(id);
        QGLCall$(GL::BufferData(GL::ELEMENT_ARRAY_BUFFER, sizeof(u32) * size, nullptr, GL::DYNAMIC_DRAW));
        return IndexBuffer { id, size };
    }

    void IndexBuffer::DestroyObject(GraphicsID id) {
        QGLCall$(GL::DeleteBuffers(1, &id));
    }

    void IndexBuffer::BindObject(GraphicsID id) {
        QGLCall$(GL::BindBuffer(GL::ELEMENT_ARRAY_BUFFER, id));
    }

    void IndexBuffer::UnbindObject() {
        QGLCall$(GL::BindBuffer(GL::ELEMENT_ARRAY_BUFFER, 0));
    }

    void IndexBuffer::SetData(Span<const u32> data, u32 dOffset) {
        Bind();
        QGLCall$(GL::BufferSubData(GL::ELEMENT_ARRAY_BUFFER, dOffset, data.ByteSize(), data.Data()));
    }

    void IndexBuffer::ClearData() {
        dataOffset = 0;
    }

    void IndexBuffer::AddData(Span<const u32> data) {
        Bind();
        QGLCall$(GL::BufferSubData(GL::ELEMENT_ARRAY_BUFFER, dataOffset * sizeof(u32), data.ByteSize(), data.Data()));
        dataOffset += (u32)data.Length();
    }
}
