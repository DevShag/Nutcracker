#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"),
	m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	
	
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Nutcracker::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	//Render
	Nutcracker::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Nutcracker::RenderCommand::Clear();


	Nutcracker::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Nutcracker::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f,1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Nutcracker::Renderer2D::EndScene();
	
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Triange Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Nutcracker::Event& event)
{
	m_CameraController.OnEvent(event);
}
