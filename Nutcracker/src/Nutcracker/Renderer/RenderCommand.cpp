#include "ncpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Nutcracker {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}