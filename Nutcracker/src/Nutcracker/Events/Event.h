#pragma once

#pragma once
#include "../Core.h"
#include <string>
#include <functional>

namespace Nucracker {

	// Events in Nutcracker are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage

	enum class EventType {
		None = 0,
		//Window Event Class
		WindowClose,
		WindowResize,
		WidowFocus,
		WindowLostFocus,
		WindowMoved,

		//Application Event Class
		AppTick,
		AppUpdate,
		AppRender,

		//keyboard Event Class
		KeyPressed,
		KeyReleased,

		//Mouse Button Event Class
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	enum  EventCategory {

		None = 0,
		EventCategoryApplication       = BIT(0),
		EventCategoryInput             = BIT(1),
		EventCategoryKeyboard          = BIT(2),
		EventCategoryMouse             = BIT(3),
		EventCategoryMouseButton       = BIT(3)

	};

	class NUTCRACKER_API Event {
		
		friend class EventDispature;

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handled = false;

	};
}

