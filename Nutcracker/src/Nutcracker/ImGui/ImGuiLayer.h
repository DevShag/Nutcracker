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

			virtual void OnAttach() override;
			virtual void OnDetach() override;
			virtual void OnImGuiRender() override;
			//virtual void OnUpdate() override;
			//void OnEvent(Event& event);

			void Begin();
			void End();

	/*private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMoveEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypeEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);*/

	private:

		float m_Time = 0.0f;
		const char* glsl_version = "#version 130";
	};


}
