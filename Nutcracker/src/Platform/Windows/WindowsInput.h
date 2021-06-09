#pragma once

#include "Nutcracker/Input.h"


namespace Nutcracker {

	class WindowsInput : public Input
	{

	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImp(int button) override;
		virtual std::pair<float, float> GetMousePositionImp() override;
		virtual float GetMouseX(int keycode) override;
		virtual float GetMouseY(int keycode) override;
	};
}



