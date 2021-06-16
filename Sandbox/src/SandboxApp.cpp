#include <Nutcracker.h>

#include "imgui/imgui.h"


//===========================================



//======================================

class ExampleLayer :public Nutcracker::Layer
{
public:
	
	ExampleLayer() :Layer("Example") 
	{
		
	}

	void OnUpdate() override {
		//NC_INFO("ExampleLayer::Update");

		if (Nutcracker::Input::IsKeyPressed(NC_KEY_TAB)) {
			NC_TRACE("Tan key is pressed");
		}
	}

	virtual void OnImGuiRender() override {

		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Nutcracker::Event& event) override {
		//NC_TRACE("{0}", event);

		if (event.GetEventType() == Nutcracker::EventType::KeyPressed) {
			Nutcracker::KeyPressedEvent& e = (Nutcracker::KeyPressedEvent&)event;
			NC_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
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