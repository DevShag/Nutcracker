#pragma once

#include<functional>

using namespace std;
using namespace std::placeholders;

void func(int a, int b, int c) {
	/*cout << "a : " + a<<std::endl;
	cout << "b : " + b;
	cout << "c : " + c;*/
	printf("a = %d \n", a);
	printf("b = %d \n", b);
	printf("c = %d \n", c);
}


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

	//auto fn1 = bind(func, _1, 2, 3);

	//auto fn2 = bind(func, 2, _1, 3);

	//fn1(10);

	//fn2(10);

	//auto fn1 = bind(func, _2, 2, _1);
	//fn1(1, 13);

	/*auto fn2 = bind(func, _1, 2, _2);
	fn2(1, 13);*/
}
#endif