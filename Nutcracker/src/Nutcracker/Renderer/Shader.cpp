#include "ncpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
//#include <glad/glad.h>


namespace Nutcracker {

	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NC_CORE_ASSERT(false, "Renderer API::None is currently not supported by Nutcracker");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGlShader(filepath);
		}

		NC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Shader * Shader::Create(const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NC_CORE_ASSERT(false, "Renderer API::None is currently not supported by Nutcracker");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGlShader(vertexSrc, fragmentSrc);
		}

		NC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	
	
}
