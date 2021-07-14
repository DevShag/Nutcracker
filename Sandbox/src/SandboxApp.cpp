#include <Nutcracker.h>

#include "imgui/imgui.h"


//===========================================



//======================================

class ExampleLayer :public Nutcracker::Layer
{
public:
	
	ExampleLayer() :Layer("Example"),
		m_Camera(-1.0f, 1.0f, -1.0f, 1.0f),
		m_CameraPosition(0.0f, 0.0f, 0.0f)
	{
		m_VertexArray.reset(Nutcracker::VertexArray::Create());


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		m_VertexBuffer.reset(Nutcracker::VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			Nutcracker::BufferLayout layout = {
			{Nutcracker::ShaderDataType::Float3, "a_Position"},
			{Nutcracker::ShaderDataType::Float4, "a_Color"}
			//{ShaderDataType::Float3, "a_Normal"}
			};
			m_VertexBuffer->SetLayout(layout);
		}

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);	

		uint32_t indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(Nutcracker::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
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

		m_Shader.reset(new Nutcracker::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate() override {
		if (Nutcracker::Input::IsKeyPressed( NC_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraMoveSpeed;
		}

		else if (Nutcracker::Input::IsKeyPressed(NC_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraMoveSpeed;
		}

		if (Nutcracker::Input::IsKeyPressed(NC_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraMoveSpeed;
		}

		else if (Nutcracker::Input::IsKeyPressed(NC_KEY_UP)) {
			m_CameraPosition.y += m_CameraMoveSpeed;
		} 

		if (Nutcracker::Input::IsKeyPressed(NC_KEY_A)) {
			m_CameraRotation += m_CameraRotationSpeed;
		}

		else if (Nutcracker::Input::IsKeyPressed(NC_KEY_D)) {
			m_CameraRotation -= m_CameraRotationSpeed;
		}

		Nutcracker::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Nutcracker::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Nutcracker::Renderer::BeginScene(m_Camera);
		{
			Nutcracker::Renderer::Submit(m_Shader, m_VertexArray);
		}

		Nutcracker::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {

		/*ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();*/
	}

	void OnEvent(Nutcracker::Event& event) override {
		//Nutcracker::EventDispatcher dispature(event);
		//dispature.Dispatch<Nutcracker::KeyPressedEvent>(NC_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	/*bool OnKeyPressedEvent(Nutcracker::KeyPressedEvent& event) {
		if (event.GetKeyCode() == NC_KEY_LEFT) {
			m_CameraPosition.x -= m_CameraSpeed;
		}

		if (event.GetKeyCode() == NC_KEY_RIGHT) {
			m_CameraPosition.x += m_CameraSpeed;
		}

		if (event.GetKeyCode() == NC_KEY_DOWN) {
			m_CameraPosition.y -= m_CameraSpeed;
		}

		if (event.GetKeyCode() == NC_KEY_UP) {
			m_CameraPosition.y += m_CameraSpeed;
		}

		return false;
	}*/

private:
	std::shared_ptr<Nutcracker::Shader> m_Shader;
	std::shared_ptr<Nutcracker::VertexArray> m_VertexArray;
	std::shared_ptr<Nutcracker::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Nutcracker::IndexBuffer> m_IndexBuffer;
	
	Nutcracker::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.1f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 0.1f;
};




class Sandbox :public Nutcracker::Application {

public:
	Sandbox() {
	    PushLayer(new ExampleLayer()); 
		//PushOverlay(new Nutcracker::ImGuiLayer());
	}

	~Sandbox() {
	}
};

Nutcracker::Application* Nutcracker::CreateApplication() {
	return new Sandbox();
}