#pragma once

#include "Nutcracker/Core.h"

namespace Nutcracker {

	class NUTCRACKER_API Input {

	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImp(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImp(); }
		inline static float GetMouseX() { return s_Instance->GetMouseX(); }
		inline static float GetMouseY() { return s_Instance->GetMouseY(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImp(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImp() = 0;
		virtual float GetMouseX(int keycode) = 0;
		virtual float GetMouseY(int keycode) = 0;

	private:
		static Input* s_Instance;
	
	};
}
