#include "ncpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
//#include <glad/glad.h>


namespace Nutcracker {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NC_CORE_ASSERT(false, "Renderer API::None is currently not supported by Nutcracker");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGlShader>(filepath);
		}

		NC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name,const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NC_CORE_ASSERT(false, "Renderer API::None is currently not supported by Nutcracker");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGlShader>(name, vertexSrc, fragmentSrc);
		}

		NC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string & name, const Ref<Shader>& shader)
	{
		NC_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists!");
		m_Shaders[name] = shader;
	}
	
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}



	Ref<Shader> ShaderLibrary::Load(const std::string & filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string & name, const std::string & filepath)
	{
		return Ref<Shader>();
	}

	Ref<Shader> ShaderLibrary::Get(const std::string & name)
	{
		NC_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string & name) const
	{
		return  m_Shaders.find(name)!=m_Shaders.end();
	}

}
