#include "RenderData.h"

#include "glp.h"
#include "GraphicsDevice.h"
#include "GLs/FrameBuffer.h"
#include "GLs/GLDebug.h"

namespace Quasi::Graphics {
	void RenderData::Transfer(RenderData& dest, RenderData&& from) {
		dest.varray = std::move(from.varray);
		dest.vbo = std::move(from.vbo);
		dest.ibo = std::move(from.ibo);
		dest.vertexData = std::move(from.vertexData);
		dest.indexData = std::move(from.indexData);
		dest.vertexOffset = from.vertexOffset;
		dest.indexOffset = from.indexOffset;

		dest.device = from.device;
		from.device = nullptr;
		dest.deviceIndex = from.deviceIndex;
		from.deviceIndex = 0;
	}

	RenderData::~RenderData() {
		Destroy();
	}

	void RenderData::PushIndex(Triplet index) {
		indexData[indexOffset + 0] = index.i;
		indexData[indexOffset + 1] = index.j;
		indexData[indexOffset + 2] = index.k;
		indexOffset += 3;
	}

	void RenderData::PushIndicesOffseted(Span<const Triplet> indices, usize objectSize) {
		const u32 iOff = vertexOffset / objectSize;
		for (const auto& i : indices)
			PushIndex(i + iOff);
	}

	void RenderData::Bind() const {
		varray.Bind();
		vbo.Bind();
		ibo.Bind();
	}

	void RenderData::Unbind() const {
		varray.Unbind();
		vbo.Unbind();
		ibo.Unbind();
	}

	void RenderData::BufferUnload() {
		vbo.ClearData();
		ibo.ClearData();
	}

	void RenderData::BufferLoad() {
		vbo.AddDataBytes(vertexData.First(vertexOffset));
		ibo.AddData     (indexData .First(indexOffset));
	}

	void RenderData::Clear() {
		vertexOffset = 0;
		indexOffset = 0;
	}

	void RenderData::Render(Shader& replaceShader, const ShaderArgs& args, bool setDefaultShaderArgs) {
		device->Render(*this, replaceShader, args, setDefaultShaderArgs);
	}

	void RenderData::RenderInstanced(Shader& replaceShader, int instances, const ShaderArgs& args, bool setDefaultShaderArgs) {
		device->RenderInstanced(*this, instances, replaceShader, args, setDefaultShaderArgs);
	}

	void RenderData::Destroy() {
		if (device) {
			OptRef prev = device; // prevent infinte loop: deleterender -> erase renderdata -> destructor
			device = nullptr;
			prev->DeleteRender(deviceIndex);
		}
	}
}
