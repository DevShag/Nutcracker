#include <Nutcracker.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/type_ptr.hpp>




class ExampleLayer :public Nutcracker::Layer
{
public:
	
	ExampleLayer() :Layer("Example"),
		m_Camera(-1.0f, 1.0f, -1.0f, 1.0f),
		m_CameraPosition(0.0f, 0.0f, 0.0f),
		m_TrianglePosition(0.0f, 0.0f, 0.0f)
	{
		m_VertexArray.reset(Nutcracker::VertexArray::Create());


		/*float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
*/


		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		m_VertexBuffer.reset(Nutcracker::VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			Nutcracker::BufferLayout layout = {
			{Nutcracker::ShaderDataType::Float3, "a_Position"},
			{Nutcracker::ShaderDataType::Float2, "a_TexCoord"}
			//{ShaderDataType::Float3, "a_Normal"}
			};
			m_VertexBuffer->SetLayout(layout);
		}

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);	

		//uint32_t indices[3] = { 0,1,2 };
		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		m_IndexBuffer.reset(Nutcracker::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;

			//set par drawcall
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position=a_Position;
				//gl_Position= vec4(a_Position,1.0);
				gl_Position= u_ViewProjection * u_Transform * vec4(a_Position,1.0);
			}


		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;

			in vec3 v_Position;
			uniform vec3 u_Color;

			void main()
			{
				color=vec4(u_Color, 1.0);
			}


		)";


		m_Shader.reset(Nutcracker::Shader::Create(vertexSrc, fragmentSrc));


		//==============================================================


		m_TextureShader.reset(Nutcracker::Shader::Create(vertexSrc, fragmentSrc));
		m_TextureShader.reset(Nutcracker::Shader::Create("assets/shaders/Texture.glsl"));

		m_Texture = Nutcracker::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Nutcracker::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Nutcracker::OpenGlShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Nutcracker::OpenGlShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Nutcracker::Timestep ts) override {

		//NC_TRACE("Delta time: {0} ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		if (Nutcracker::Input::IsKeyPressed( NC_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}

		else if (Nutcracker::Input::IsKeyPressed(NC_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}

		if (Nutcracker::Input::IsKeyPressed(NC_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}

		else if (Nutcracker::Input::IsKeyPressed(NC_KEY_UP)) {
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		} 

		if (Nutcracker::Input::IsKeyPressed(NC_KEY_A)) {
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}

		else if (Nutcracker::Input::IsKeyPressed(NC_KEY_D)) {
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}


		//============================================

		if (Nutcracker::Input::IsKeyPressed(NC_KEY_J)) {
			m_TrianglePosition.x -= m_TriangleMoveSpeed * ts;
		}

		else if (Nutcracker::Input::IsKeyPressed(NC_KEY_L)) {
			m_TrianglePosition.x += m_TriangleMoveSpeed * ts;
		}

		if (Nutcracker::Input::IsKeyPressed(NC_KEY_K)) {
			m_TrianglePosition.y -= m_TriangleMoveSpeed * ts;
		}

		else if (Nutcracker::Input::IsKeyPressed(NC_KEY_I)) {
			m_TrianglePosition.y += m_TriangleMoveSpeed * ts;
		}

		Nutcracker::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Nutcracker::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Nutcracker::Renderer::BeginScene(m_Camera);
		{
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));

			glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
			glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

			std::dynamic_pointer_cast<Nutcracker::OpenGlShader>(m_Shader)->Bind();
			std::dynamic_pointer_cast<Nutcracker::OpenGlShader>(m_Shader)->UploadUniformFloat3("u_Color", m_Color);

			for (int i = 0; i < 20; i++) {
				
				for (int j = 0; j < 20; j++) {
					glm::vec3 pos(i*0.11f, j*0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)*scale;
					Nutcracker::Renderer::Submit(m_Shader, m_VertexArray, transform);
				}
			}

			m_Texture->Bind();
			Nutcracker::Renderer::Submit(m_TextureShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			m_ChernoLogoTexture->Bind();
			Nutcracker::Renderer::Submit(m_TextureShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		}

		Nutcracker::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {

		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Triange Color", glm::value_ptr(m_Color));
		ImGui::End();
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
	Nutcracker::Ref<Nutcracker::Shader> m_Shader, m_TextureShader;
	Nutcracker::Ref<Nutcracker::VertexArray> m_VertexArray;
	Nutcracker::Ref<Nutcracker::VertexBuffer> m_VertexBuffer;
	Nutcracker::Ref<Nutcracker::IndexBuffer> m_IndexBuffer;

	Nutcracker::Ref<Nutcracker::Texture2D> m_Texture, m_ChernoLogoTexture;
	
	Nutcracker::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 30.0f;

	glm::vec3 m_Color = { 0.2f, 0.3f, 0.7f };

	glm::vec3 m_TrianglePosition;
	float m_TriangleMoveSpeed = 5.0f;
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