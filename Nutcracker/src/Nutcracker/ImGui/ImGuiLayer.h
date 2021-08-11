#pragma once

#include "Nutcracker/Layer.h"

namespace Nutcracker {

	class NUTCRACKER_API ImGuiLayer: public Layer
	{
		public:
			ImGuiLayer();
			~ImGuiLayer();

			virtual void OnAttach() override;
			virtual void OnDetach() override;
			virtual void OnImGuiRender() override;

			void Begin();
			void End();

	private:

		float m_Time = 0.0f;
		const char* glsl_version = "#version 130";
	};


}
