#include <Nutcracker.h>

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

	void OnEvent(Nutcracker::Event& event) override {
		//NC_TRACE("{0}", event);

		if (event.GetEventType() == Nutcracker::EventType::KeyPressed) {
			Nutcracker::KeyPressedEvent& e = (Nutcracker::KeyPressedEvent&)event;
			NC_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};


class ExampleLayer2 :public Nutcracker::Layer
{
public:

	ExampleLayer2() :Layer("Example2")
	{

	}
};

class Sandbox :public Nutcracker::Application {

public:
	Sandbox() {
	    PushLayer(new ExampleLayer());
		//PushLayer(new ExampleLayer2());
		PushOverlay(new Nutcracker::ImGuiLayer());
	}

	~Sandbox() {
	}
};

Nutcracker::Application* Nutcracker::CreateApplication() {
	return new Sandbox();
}