#include "bubblepch.h"
#include "Application.h"

#include "Log.h"

namespace bubble
{
	Application::Application()
		: m_window(Window::Create())
	{
		m_window->setEventCallback([this](Event& event) { onEvent(event); });
	}

	Application::~Application()
	{
		
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}

	void Application::run()
	{
		while (m_running) 
		{
			m_window->onUpdate();
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) { return OnWindowClose(e); });

		BUBBLE_CORE_TRACE(e);
	}
}