#include "bubblepch.h"
#include "Application.h"

#include "Log.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

#include "Bubble/Renderer/Renderer.h"
#include "Bubble/Renderer/Camera.h"

#include "Input.h"

#include <imgui.h>
#include <GLFW/glfw3.h>

namespace bubble
{
	Application* Application::m_instance = nullptr;

	Application::Application(const std::string& name)
		: m_window(Window::Create(WindowProps(name)))
		, m_imGuiLayer(new ImGuiLayer())
	{
		BUBBLE_CORE_ASSERT(!m_instance,  "Application already exists");
		m_instance = this;

		m_window->setEventCallback([this](Event& event) { onEvent(event); });
        Renderer::Init();

		pushOverlay(m_imGuiLayer);
	}

	Application::~Application()
	{
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}

    bool Application::onWindowResize(WindowResizeEvent& e)
    {
        Renderer::OnWindowResize(e.getWidth(), e.getHeight());
        return false;
    }

	void Application::run()
	{
		while (m_running)
		{
            const auto t = static_cast<float>(glfwGetTime());
            const auto dt = t - m_time;
            m_time = t;

			for (auto layer : m_layerStack)
				layer->onUpdate(dt);

			m_imGuiLayer->begin();
			for (auto layer : m_layerStack)
				layer->onImGuiRender();

			m_imGuiLayer->end();
			m_window->onUpdate();
		}
	}

    void Application::quit()
    {
        m_running = false;
    }

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) { return onWindowClose(e); });
        dispatcher.dispatch<WindowResizeEvent>([this](WindowResizeEvent& e) { return onWindowResize(e); });

		for (auto it = m_layerStack.rbegin(), end = m_layerStack.rend(); it != end; ++it)
		{
			(*it)->onEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* layer)
	{
		m_layerStack.pushOverlay(layer);
		layer->onAttach();
	}

} // namespace bubble
