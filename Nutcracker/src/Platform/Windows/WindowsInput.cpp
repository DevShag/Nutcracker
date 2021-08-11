#include "ncpch.h"
#include "WindowsInput.h"
#include "Nutcracker/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Nutcracker {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state =glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::IsMouseButtonPressedImp(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, button);
		return state == GLFW_PRESS ;
	}


	std::pair<float, float> WindowsInput::GetMousePositionImp()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos , (float)ypos };
	}


	float WindowsInput::GetMouseX(int keycode)
	{
		auto[x, y] = GetMousePosition();
		return x;
	}


	float WindowsInput::GetMouseY(int keycode)
	{
		auto[x, y] = GetMousePosition();
		return y;
	}
}
