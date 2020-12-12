#pragma once

#include "Core.h"

namespace Nutcracker {

	class NUTCRACKER_API Application
	{

	public:
		Application();
		virtual ~Application();

		void Run();

	};

	//To be defined in Client
	Application* CreateApplication();

}

