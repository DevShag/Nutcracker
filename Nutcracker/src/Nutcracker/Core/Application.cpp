#include "ncpch.h"
#include "Application.h"
#include "Nutcracker/Core/Log.h"
#include "Input.h"

#include "GLFW/glfw3.h"


#include "Nutcracker/Renderer/RenderCommand.h"
#include "Nutcracker/Renderer/Renderer.h"




namespace Nutcracker {

   #define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	//auto fn1 = bind(func, _1, 2, 3);

	


	Application::Application()
		
	{
		NC_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_ImGuiLayer =new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//======================
		//glGenVertexArrays(1, &m_VertexArray);
		//glBindVertexArray(m_VertexArray);

	
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event & e)
	{
		EventDispatcher dispature(e);
		dispature.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispature.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		//NC_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			//=================
			if (e.m_Handled) {
				break;

			}
		}

	}

	void Application::PushLayer(Layer * layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer * layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Run()
	{
		
		while (m_Running)
		{		
			float time = (float)glfwGetTime();  //later it should be in Platform floder
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack) {
					layer->OnUpdate(timestep);
				}			
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent & e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

}

	