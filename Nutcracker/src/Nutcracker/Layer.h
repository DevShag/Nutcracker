#pragma once
#include "Core.h"
#include "Nutcracker/Events/Event.h"
#include "Nutcracker/Core/Timestep.h"

namespace Nutcracker {


	class NUTCRACKER_API Layer
	{

	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& event) {};

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;

	};


}

