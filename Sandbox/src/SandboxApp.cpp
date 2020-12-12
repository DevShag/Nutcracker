#include <Nutcracker.h>

class Sandbox :public Nutcracker::Application {

public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Nutcracker::Application* CreateApplication() {
	return new Sandbox();
}