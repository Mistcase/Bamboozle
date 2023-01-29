#pragma once

#include "Bubble/bubblepch.h"
#include "Bubble/Core.h"

namespace bubble
{
	// TODO: add event buffering

	enum class EventType
	{
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,

		AppTick,
		AppUpdate,
		AppRender,

		KeyPressed,
		KeyReleased,
		KeyTyped,

		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	enum EventCategory
	{
		// Exists just for filtering events
		None = 0,
		EventCategoryApplication    = 1,
		EventCategoryInput          = 1 << 1,
		EventCategoryKeyboard       = 1 << 2,
		EventCategoryMouse          = 1 << 3,
		EventCategoryMouseButton    = 1 << 4
	};

#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::type; }\
								EventType getEventType() const override { return GetStaticType(); }\
								const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) int getCategoryFlags() const override { return category; }

	class BUBBLE_API Event
	{
		friend class EventDispatcher;

	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(EventCategory category)
		{
			return getCategoryFlags() & category;
		}

		bool handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using FnDispatchEvent = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			: m_event(event)
		{
		}

		template<typename T>
		bool dispatch(FnDispatchEvent<T> func)
		{
			if (m_event.getEventType() == T::GetStaticType())
			{
				m_event.handled = func(*(T*)&m_event);
				return true;
			}
			return false;
		}

	private:
		Event& m_event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}

} // namespace bubble
