#pragma once

#include "Nutcracker/Layer.h"
#include "Nutcracker/Events/KeyEvent.h"
#include "Nutcracker/Events/MouseEvent.h"
#include "Nutcracker/Events/ApplicationEvent.h"

namespace Nutcracker {

	class NUTCRACKER_API ImGuiLayer: public Layer
	{
		public:
			ImGuiLayer();
			~ImGuiLayer();

			void OnAttach();
			void OnDetach();
			void OnUpdate();
			void OnEvent(Event& event);

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMoveEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypeEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:

		float m_Time = 0.0f;

	};


}
