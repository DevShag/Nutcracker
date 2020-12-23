#include "ncpch.h"
#include "Application.h"
#include "Nutcracker/Events/ApplicationEvent.h"
#include "Nutcracker/Log.h"

namespace Nutcracker {
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		WindowResizeEvent e(1920, 1080);
		if (!e.IsInCategory(EventCategoryApplication)) {
			NC_TRACE(e);

		}
		

		while (true)
		{

		}
	}
}