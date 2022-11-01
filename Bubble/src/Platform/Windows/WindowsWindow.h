#pragma once

#include "Bubble/Window.h"

#include <GLFW/glfw3.h>

namespace bubble
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override { return m_data.width; }
		inline unsigned int getHeight() const override { return m_data.height; }

		// Window attributes
		inline void setEventCallback(const FnEventCallback& callback) override { m_data.eventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;

	    void* getNativeWindow() const override;

	private:
		virtual void init(const WindowProps& props);
		virtual void shutdown();

	private:
		GLFWwindow* m_window;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vSync;

			FnEventCallback eventCallback;
		};

		WindowData m_data;
	};

} // namespace bubble