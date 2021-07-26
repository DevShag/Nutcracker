#include "ncpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"


namespace Nutcracker {

	Ref<Texture2D> Texture2D::Create(const std::string & path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NC_CORE_ASSERT(false, "Renderer API::None is currently not supported by Nutcracker");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);			
		}

		NC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return Ref<Texture2D>();
	}
}
