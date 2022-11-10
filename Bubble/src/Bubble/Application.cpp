#include "bubblepch.h"
#include "Application.h"

#include "Log.h"
#include "Renderer/Buffer.h"

#include <glad/glad.h>

#include "Input.h"

namespace bubble
{
	Application* Application::m_instance = nullptr;

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
		switch (type)
		{
		case bubble::ShaderDataType::Float:
		case bubble::ShaderDataType::Float2:
		case bubble::ShaderDataType::Float3:
		case bubble::ShaderDataType::Float4:
        case bubble::ShaderDataType::Mat3:
		case bubble::ShaderDataType::Mat4:
			return GL_FLOAT;

		case bubble::ShaderDataType::Int:
		case bubble::ShaderDataType::Int2:
		case bubble::ShaderDataType::Int3:
		case bubble::ShaderDataType::Int4:
            return GL_UNSIGNED_INT;

		case bubble::ShaderDataType::Bool:
			return GL_BOOL;

		default:
			break;
		}

        BUBBLE_CORE_ASSERT(false, "Unknown shader data type");
        return 0;
    };

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
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f
		};

        m_vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        {
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float4, "a_Color" }
            };

            m_vertexBuffer->setLayout(layout);
        }

        int index = 0;
        const auto& layout = m_vertexBuffer->getLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                                  element.getComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.type),
                                  element.normalized ? GL_TRUE : GL_FALSE,
                                  layout.getStride(),
                                  (const void*)element.offset);
            index++;
        }

		unsigned int indices[] = { 0, 1, 2 };
        m_indexBuffer.reset(IndexBuffer::Create(indices, std::size(indices)));

        std::string vertexSource = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        out vec4 v_Color;

        void main()
        {
            v_Color = a_Color;
            gl_Position = vec4(a_Position, 1.0);
        }
        )";
        std::string fragmentSource = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec4 v_Color;

        void main()
        {
            color = v_Color;
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
