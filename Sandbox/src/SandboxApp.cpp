#include <Nutcracker.h>

class ExampleLayer :public Nutcracker::Layer
{
public:
	
	ExampleLayer() :Layer("Example") 
	{

	}

	void OnUpdate() override {
		//NC_INFO("ExampleLayer::Update");
	}

	void OnEvent(Nutcracker::Event& event) override {
		//NC_TRACE("{0}", event);
	}
};

class Sandbox :public Nutcracker::Application {

public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Nutcracker::ImGuiLayer());
	}

	~Sandbox() {
	}
};

Nutcracker::Application* Nutcracker::CreateApplication() {
	return new Sandbox();
}