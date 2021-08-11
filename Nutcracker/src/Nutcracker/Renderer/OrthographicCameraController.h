#pragma once

#include "Nutcracker/Renderer/OrthographicCamera.h"
#include "Nutcracker/Core/Timestep.h"

#include "Nutcracker/Events/MouseEvent.h"
#include "Nutcracker/Events/ApplicationEvent.h"

namespace Nutcracker
{
	class OrthographicCameraController
	{
	public:

		OrthographicCameraController(float aspectRatio, bool rotation=false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		void SetZoomLevel(float level) { m_ZoomLevel = level; }
		float GetZoomLevel() const { return m_ZoomLevel; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;
		bool m_Rotation;
		float m_CameraRotation = 0.0f;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraTranslationSpeed = 1.0f, m_CameraRotationSpeed=1.0f;
	};
}

