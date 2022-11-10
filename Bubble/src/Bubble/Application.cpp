#include "bubblepch.h"
#include "Application.h"

#include "Log.h"
#include "Renderer/Buffer.h"

#include <glad/glad.h>

#include "Input.h"

namespace bubble
{
	Application* Application::m_instance = nullptr;

	Application::Application()
		: m_window(Window::Create())
		, m_imGuiLayer(new ImGuiLayer())
	{
		BUBBLE_CORE_ASSERT(!m_instance, "Application already exists");
		m_instance = this;

		m_window->setEventCallback([this](Event& event) { onEvent(event); });

		pushOverlay(m_imGuiLayer);

		glGenVertexArrays(1, &m_vertexArray);
		glBindVertexArray(m_vertexArray);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f, 0.5f, 0.0f
		};

        m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		unsigned int indices[] = { 0, 1, 2 };
        m_indexBuffer.reset(IndexBuffer::Create(indices, std::size(indices)));

        std::string vertexSource = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;

        out vec3 v_Position;

        void main()
        {
            v_Position = a_Position;
            gl_Position = vec4(a_Position, 1.0);
        }
        )";
        std::string fragmentSource = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_Position;

        void main()
        {
            color = vec4(v_Position + vec3(0.5), 1.0f);
        }
        )";

        m_shader = std::make_unique<Shader>(vertexSource, fragmentSource);
	}

	Application::~Application()
	{
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}

	void Application::run()
	{
		while (m_running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

            m_shader->bind();
			m_vertexBuffer->bind();
			m_indexBuffer->bind();
			glBindVertexArray(m_vertexArray);
			glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

			for (auto layer : m_layerStack)
				layer->onUpdate();

			m_imGuiLayer->begin();
			for (auto layer : m_layerStack)
				layer->onImGuiRender();
			m_imGuiLayer->end();

			m_window->onUpdate();
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) { return onWindowClose(e); });

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
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* layer)
	{
		m_layerStack.pushOverlay(layer);
		layer->onAttach();
	}

} // namespace bubble
