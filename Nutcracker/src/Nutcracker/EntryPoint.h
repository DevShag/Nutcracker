#pragma once


#ifdef NC_PLATFORM_WINDOWS

extern Nutcracker::Application* Nutcracker::CreateApplication();

int main(int argc, char** argv) {
	printf("Nutcracker Engine2");
	
	
	auto app = Nutcracker::CreateApplication();
	app->Run();
	delete app;
}
#endif