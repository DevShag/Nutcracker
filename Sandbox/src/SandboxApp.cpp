#include <Nutcracker.h>

class Sandbox :public Nutcracker::Application {

public:
	Sandbox() {

	}

	~Sandbox() {
	}
};

Nutcracker::Application* Nutcracker::CreateApplication() {
	return new Sandbox();
}