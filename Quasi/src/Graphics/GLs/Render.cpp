#include "Render.h"
#include <glp.h>
#include "GLDebug.h"
#include "GraphicsDevice.h"
#include "VertexArray.h"
#include "../RenderData.h"

namespace Quasi::Graphics::Render {
    void Draw(const VertexArray& vertexArr, const IndexBuffer& indexBuff, const ShaderProgram& shader) {
        vertexArr.Bind();
        indexBuff.Bind();
        shader.Bind();
        QGLCall$(GL::DrawElements(GL::TRIANGLES, (int)indexBuff.GetUsedLength(), GL::UNSIGNED_INT, nullptr));
    }

    void DrawInstanced(const VertexArray& vertexArr, const IndexBuffer& indexBuff, const ShaderProgram& shader, int instances) {
        vertexArr.Bind();
        indexBuff.Bind();
        shader.Bind();
        QGLCall$(GL::DrawElementsInstanced(GL::TRIANGLES, (int)indexBuff.GetUsedLength(), GL::UNSIGNED_INT, nullptr, instances));
    }

    void Draw(const RenderData& dat, const ShaderProgram& s) {
        Draw(dat.varray, dat.ibo, s);
    }

    void Draw(const RenderData& dat) {
        Draw(dat, dat.shader);
    }

    void DrawInstanced(const RenderData& dat, const ShaderProgram& s, int instances) {
        DrawInstanced(dat.varray, dat.ibo, s, instances);
    }

    void DrawInstanced(const RenderData& dat, int instances) {
        DrawInstanced(dat, dat.shader, instances);
    }

    void DrawScreenQuad(const ShaderProgram& s) {
        GraphicsDevice::GetEmptyVAO().Bind();
        s.Bind();
        IndexBuffer::UnbindObject();
        QGLCall$(GL::DrawArrays(GL::TRIANGLES, 0, 3));
    }

    void Clear(const BufferBit bit) {
        QGLCall$(GL::Clear((int)bit));
    }

    void SetRenderMode(const RenderMode mode) {
        QGLCall$(GL::PolygonMode(GL::FRONT_AND_BACK, (uint)mode));
    }

    void SetPointSize(float size) {
        QGLCall$(GL::PointSize(size));
    }

    void SetClearColor(const Math::fColor& color) {
        QGLCall$(GL::ClearColor(color.r, color.g, color.b, color.a));
    }

    void Enable(const Capability cap) {
        QGLCall$(GL::Enable((int)cap));
    }

    void Disable(const Capability cap) {
        QGLCall$(GL::Disable((int)cap));
    }

    void UseDepthFunc(const CmpOperation op) {
        QGLCall$(GL::DepthFunc((int)op));
    }

    void UseStencilTest(const CmpOperation op, const int ref, const int mask) {
        QGLCall$(GL::StencilFunc((int)op, ref, mask));
    }

    void UseStencilWriteMask(const int mask) {
        QGLCall$(GL::StencilMask(mask));
    }

    void UseStencilWriteOp(StencilOperation stencilFail, StencilOperation depthFail, StencilOperation pass) {
        QGLCall$(GL::StencilOp((int)stencilFail, (int)depthFail, (int)pass));
    }

    void UseAlphaFunc(const CmpOperation op, const float ref) {
        QGLCall$(GL::AlphaFunc((int)op, ref));
    }

    void UseBlendConstColor(const Math::fColor& ref) {
        QGLCall$(GL::BlendColor(ref.r, ref.g, ref.b, ref.a));
    }

    void UseBlendFunc(const BlendFactor src, const BlendFactor dest) {
        QGLCall$(GL::BlendFunc((int)src, (int)dest));
    }

    void UseBlendFuncSeparate(BlendFactor src, BlendFactor dest, BlendFactor srcAlpha, BlendFactor destAlpha) {
        QGLCall$(GL::BlendFuncSeparate((int)src, (int)dest, (int)srcAlpha, (int)destAlpha));
    }

    void SetCullFace(FacingMode facing) {
        QGLCall$(GL::CullFace((int)facing));
    }

    void SetFrontFacing(OrientationMode   orientation) {
        QGLCall$(GL::FrontFace((int)orientation));
    }

    void SetColorWrite(BufferMode mode) {
        QGLCall$(GL::DrawBuffer((int)mode));
    }

    void MemoryBarrier(int barrierBits) {
        QGLCall$(GL::MemoryBarrier(barrierBits));
    }

    void FinishPrevious() {
        GL::Finish();
    }

    void ReadFromFrontBuffer() {
        GL::ReadBuffer(GL::FRONT);
    }

    void ReadFromBackBuffer() {
        GL::ReadBuffer(GL::BACK);
    }
}
