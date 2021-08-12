#include "ncpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Nutcracker {


	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NC_CORE_ASSERT(false, "Renderer API::None is currently not supported by Nutcracker");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}

		NC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}


	
}
