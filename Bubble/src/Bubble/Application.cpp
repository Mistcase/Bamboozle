#include "bubblepch.h"
#include "Application.h"

#include "Log.h"

#include <glad/glad.h>

namespace bubble
{
	Application::Application()
		: m_window(Window::Create())
	{
		m_window->setEventCallback([this](Event& event) { onEvent(event); });

		unsigned int id;
		glGenVertexArrays(1, &id);
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
			for (auto layer : m_layerStack)
				layer->onUpdate();

			m_window->onUpdate();
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) { return OnWindowClose(e); });

		BUBBLE_CORE_TRACE(e);

		for (auto it = std::prev(m_layerStack.end()); it != m_layerStack.begin(); --it)
		{
			(*it)->onEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* layer)
	{
		m_layerStack.pushOverlay(layer);
	}
}