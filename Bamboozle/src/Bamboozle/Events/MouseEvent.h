#pragma once

#include "Event.h"

#include <sstream>

namespace bbzl
{
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y)
            : m_mouseX(x)
            , m_mouseY(y)
        {
        }

        inline float getX() const
        {
            return m_mouseX;
        }
        inline float getY() const
        {
            return m_mouseY;
        }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_mouseX, m_mouseY;
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset)
            : m_XOffset(xOffset)
            , m_YOffset(yOffset)
        {
        }

        inline float getXOffset() const
        {
            return m_XOffset;
        }
        inline float getYOffset() const
        {
            return m_YOffset;
        }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << getXOffset() << ", " << getYOffset();
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_XOffset, m_YOffset;
    };

    class MouseButtonEvent : public Event
    {
    public:
        inline int getMouseButton() const
        {
            return m_Button;
        }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    protected:
        MouseButtonEvent(int button)
            : m_Button(button)
        {
        }

        int m_Button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button)
        {
        }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button)
        {
        }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

	class MouseCursorVisibilityChanged : public Event
	{
	public:
		MouseCursorVisibilityChanged(bool isVisible)
			: m_isVisible(isVisible)
		{
		}

		bool isVisible() const
		{
			return m_isVisible;
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseCursorVisibilityChanged)

		private:
		    bool m_isVisible;
	};

} // namespace bbzl
