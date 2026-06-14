#pragma once

#include "GLs/VertexArray.h"
#include "GLs/VertexBuffer.h"
#include "GLs/IndexBuffer.h"
#include "GLs/Shader.h"
#include "GLs/VertexElement.h"

namespace Quasi::Graphics {
	class FrameBuffer;
}

namespace Quasi::Graphics {
	class GraphicsDevice;

	template <IVertex Vtx> class Mesh;

    template <class>
	class RenderObject;
    
	class RenderData {
	public:
		VertexArray varray;
		VertexBuffer vbo;
		IndexBuffer ibo;

	    Math::Matrix3D projection = Math::Matrix3D::OrthoProjection({{ { -4.0f, 4.0f }, { -3.0f, 3.0f }, { 0.1f, 100.0f } }});
	    Math::Matrix3D camera {};
	    Shader shader = {}; // shader can be null if renderId is 0

		ArrayBox<byte> vertexData;
		usize vertexOffset = 0;
		ArrayBox<u32> indexData;
		usize indexOffset = 0;

		OptRef<GraphicsDevice> device;
		usize deviceIndex = 0;

		friend class GraphicsDevice;

		explicit RenderData(GraphicsDevice& gd, usize vsize, usize isize, usize vertSize, const VertexBufferLayout& layout) :
			varray(VertexArray::New()), vbo(VertexBuffer::New(vsize * vertSize)), ibo(IndexBuffer::New(isize)),
			vertexData(ArrayBox<byte>::AllocateUninit(vsize * vertSize)), indexData(ArrayBox<u32>::AllocateUninit(isize)), device(gd) {
			varray.Bind();
			varray.AddBuffer(layout);
		}

		RenderData(const RenderData&) = delete;
		RenderData& operator=(const RenderData&) = delete;

		static void Transfer(RenderData& dest, RenderData&& from);
		RenderData(RenderData&& rd) noexcept : device(rd.device) { Transfer(*this, std::move(rd)); }
		RenderData& operator=(RenderData&& rd) noexcept { Transfer(*this, std::move(rd)); return *this; }

		~RenderData();

		template <class T> void PushVertex(const T& vertex);
		void PushIndex(Triplet index);
		void PushIndicesOffseted(Span<const Triplet> indices, usize objectSize);

		void Bind() const;
		void Unbind() const;

		void BufferUnload();
		void BufferLoad();

		void Clear();
		template <class T>
		void Add(const Mesh<T>& mesh) {
			Memory::MemCopy(vertexData.Data() + vertexOffset, mesh.vertices.Data(), mesh.vertices.ByteSize());
			Memory::MemCopy(indexData.Data()  + indexOffset,  mesh.indices.Data(),  mesh.indices.ByteSize());
			// increment indices
			for (usize i = 0; i < mesh.indices.Length() * 3; ++i) {
				indexData[indexOffset + i] += vertexOffset / sizeof(T);
			}
			vertexOffset += mesh.vertices.ByteSize();
			indexOffset  += mesh.indices.Length() * 3;
		}

		void Destroy();

		void Render(Shader& replaceShader, const ShaderArgs& args = {}, bool setDefaultShaderArgs = true);
		void Render(const ShaderArgs& args = {}, bool setDefaultShaderArgs = true) { Render(shader, args, setDefaultShaderArgs); }

		void RenderInstanced(Shader& replaceShader, int instances, const ShaderArgs& args = {}, bool setDefaultShaderArgs = true);
		void RenderInstanced(int instances, const ShaderArgs& args = {}, bool setDefaultShaderArgs = true) { RenderInstanced(shader, instances, args, setDefaultShaderArgs); }

		friend class GraphicsDevice;
		template <IVertex T> friend class Mesh;
		template <class T> friend class RenderObject;
	};

	template <class T> void RenderData::PushVertex(const T& vertex) {
		const byte* rawbytes = Memory::TransmutePtr<const byte>(&vertex);
		Memory::MemCopyNoOverlap(&vertexData[vertexOffset], rawbytes, sizeof(T));
		vertexOffset += sizeof(T);
	}
}
