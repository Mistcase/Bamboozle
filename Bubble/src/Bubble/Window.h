#pragma once

#include "bubblepch.h"

#include "Bubble/Core.h"
#include "Bubble/Events/Event.h"

namespace bubble {

	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string& _title = "Bubble Engine",
			unsigned int _width = 1280,
			unsigned int _height = 720)
			: title(_title), width(_width), height(_height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class BUBBLE_API Window
	{
	public:
		using FnEventCallback = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		// Window attributes
		virtual void setEventCallback(const FnEventCallback& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

}