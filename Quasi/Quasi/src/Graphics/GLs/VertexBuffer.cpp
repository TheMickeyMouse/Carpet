#include "VertexBuffer.h"

#include <glp.h>

#include "GLDebug.h"

namespace Quasi::Graphics {
    VertexBuffer::VertexBuffer(GraphicsID id, u32 size) : GLObject(id), bufferSize(size) {}

    VertexBuffer VertexBuffer::New(u32 size) {
        GraphicsID id;
        QGLCall$(GL::GenBuffers(1, &id));
        BindObject(id);
        QGLCall$(GL::BufferData(GL::ARRAY_BUFFER, size, nullptr, GL::DYNAMIC_DRAW));
        return VertexBuffer { id, size };
    }

    void VertexBuffer::DestroyObject(GraphicsID id) {
        QGLCall$(GL::DeleteBuffers(1, &id));
    }

    void VertexBuffer::BindObject(GraphicsID id) {
        QGLCall$(GL::BindBuffer(GL::ARRAY_BUFFER, id));
    }

    void VertexBuffer::UnbindObject() {
        QGLCall$(GL::BindBuffer(GL::ARRAY_BUFFER, 0));
    }

    void VertexBuffer::SetDataBytes(Span<const byte> data) {
        Bind();
        QGLCall$(GL::BufferSubData(GL::ARRAY_BUFFER, 0, (int)data.ByteSize(), data.Data()));
    }

    void VertexBuffer::ClearData() {
        dataOffset = 0;
    }

    void VertexBuffer::AddDataBytes(Span<const byte> data) {
        Bind();
        QGLCall$(GL::BufferSubData(GL::ARRAY_BUFFER, (int)dataOffset, (int)data.ByteSize(), data.Data()));
        dataOffset += data.ByteSize();
    }
}
