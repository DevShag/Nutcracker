#pragma once

#include "Nutcracker.h"


class Sandbox2D : public Nutcracker::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	
	virtual void OnUpdate(Nutcracker::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Nutcracker::Event& event) override;

private:
	Nutcracker::OrthographicCameraController m_CameraController;
	//Temp
	Nutcracker::Ref<Nutcracker::VertexArray> m_SquareVA;
	Nutcracker::Ref<Nutcracker::Shader>m_FlatColorShader;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.7f, 1.0f };
};

