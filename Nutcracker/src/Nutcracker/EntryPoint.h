#pragma once


#ifdef NC_PLATFORM_WINDOWS

extern Nutcracker::Application* Nutcracker::CreateApplication();

int main(int argc, char** argv) {
	printf("Nutcracker Engine \n \n");
	
	Nutcracker::Log::Init();
	NC_CORE_WARN("Initialized Log!");
	NC_INFO("Hello");
	
	auto app = Nutcracker::CreateApplication();
	app->Run();
	delete app;
}
#endif