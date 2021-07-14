#pragma once

#include "Nutcracker/Renderer/Buffer.h"

namespace Nutcracker {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:

		OpenGLVertexBuffer(float* vertices, uint32_t count);
		virtual ~OpenGLVertexBuffer();

		// Inherited via VertexBuffer
		virtual void Bind() const override;

		virtual void Unbind() const override;

		virtual const BufferLayout & GetLayout() const override;

		virtual void SetLayout(const BufferLayout & layout) override;
	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;


		// Inherited via VertexBuffer
		

	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:

		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();

		// Inherited via VertexBuffer
		virtual void Bind() const override;

		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override;// { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;


		// Inherited via IndexBuffer

	};
}
