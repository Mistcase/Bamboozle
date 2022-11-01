#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Window.h"

class WindowCloseEvent;

namespace bubble
{
	class BUBBLE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);

	    inline static Application& GetInstance() { return *m_instance; }
		inline Window& getWindow() { return *m_window; }

	private:
		bool onWindowClose(WindowCloseEvent& e);

	private:
		static Application* m_instance;

		std::unique_ptr<Window> m_window;
		bool m_running = true;

		LayerStack m_layerStack;
	};

	// Have to be defined by client
	Application* CreateApplication();

} // namespace bubble
