#include "ncpch.h"
#include "Application.h"
#include "Nutcracker/Log.h"
#include "Input.h"
#include "glm/glm.hpp"


#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"




namespace Nutcracker {

   #define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	//auto fn1 = bind(func, _1, 2, 3);

	


	Application::Application()
		:m_Camera(-1.0f, 1.0f, -1.0f, 1.0f)
	{
		NC_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer =new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//======================
		//glGenVertexArrays(1, &m_VertexArray);
		//glBindVertexArray(m_VertexArray);

		m_VertexArray.reset(VertexArray::Create());
		

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		{
			BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}
			//{ShaderDataType::Float3, "a_Normal"}
			};
			m_VertexBuffer->SetLayout(layout);
		}

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		/*uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE: GL_FALSE, 
				m_VertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset);

			index++;
		}*/
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		uint32_t indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;

			//set par drawcall
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position=a_Position;
				gl_Position= u_ViewProjection * vec4(a_Position,1.0);
				v_Color=a_Color;
			}


		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color=v_Color;
			}


		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event & e)
	{
		EventDispatcher dispature(e);
		dispature.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
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
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			m_Camera.SetPosition({ 0.5f,0.5f,0.0f });
			m_Camera.SetRotation(45.0f);

			Renderer::BeginScene(m_Camera);
			{			
				Renderer::Submit(m_Shader,m_VertexArray);
			}
			
			Renderer::EndScene();

			//glBindVertexArray(m_VertexArray);
			//m_VertexArray->Bind();

			//Draw Call
			//glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
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

}

	