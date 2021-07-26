#pragma once

#include "Nutcracker/Renderer/VertexArray.h"
#include <vector>

namespace Nutcracker {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();
		// Inherited via VertexArray
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
		virtual std::vector<Ref<VertexBuffer>> GetVertexBuffer() override;
		virtual Ref<IndexBuffer> GetIndexBuffer() override;
		

	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;		
	};
}
