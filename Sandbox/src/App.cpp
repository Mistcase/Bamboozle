#include <Bubble.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include "ImGui/imgui.h"
#include "glm/ext/matrix_transform.hpp"

class ExampleLayer : public bubble::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
        auto& window = bubble::Application::GetInstance().getWindow();
        m_camera = std::make_unique<bubble::Camera>(window.getWidth(), window.getHeight());
        m_camera->setPosition(glm::vec3(0.0f));

        m_vertexArray.reset(bubble::VertexArray::Create());
		float vertices[] = {
            0.0f,            0.0f,            0.0f,
            m_rectangleSize, 0.0f,            0.0f,
            m_rectangleSize, m_rectangleSize, 0.0f,
            0.0f,            m_rectangleSize, 0.0f,
		};

		unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
        m_indexBuffer.reset(bubble::IndexBuffer::Create(indices, std::size(indices)));
        m_vertexArray.reset(bubble::VertexArray::Create());
        auto vertexBuffer = bubble::Ref<bubble::VertexBuffer>(bubble::VertexBuffer::Create(vertices, sizeof(vertices)));
        vertexBuffer->setLayout({
                { bubble::ShaderDataType::Float3, "a_Position" }
            });

        m_vertexArray->addVertexBuffer(vertexBuffer);
        m_vertexArray->setIndexBuffer(m_indexBuffer);

        std::string vertexSource = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;

        uniform mat4 u_VP;
        uniform mat4 u_Transform;
        uniform vec4 u_Color;
        out vec4 v_Color;

        void main()
        {
            v_Color = u_Color;
            gl_Position = u_VP * u_Transform * vec4(a_Position, 1.0);
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

        m_shader.reset(bubble::Shader::Create(vertexSource, fragmentSource));
	}

	void onUpdate(float dt) override
	{
        bubble::Renderer::BeginScene(m_camera.get());
        {
            bubble::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
            bubble::RenderCommand::Clear();

            auto idx = 0;
            for (int x = 0; x < 10; x++)
            {
                for (int y = 0; y < 10; y++)
                {
                    const auto o = 1.1f * m_rectangleSize;
                    const auto transform = glm::translate(glm::mat4(1.0f), m_objectPosition + glm::vec3(o * x, o * y, 0.0f));

                    static_cast<const bubble::OpenGLShader*>(m_shader.get())->setUniform4f("u_Color", (idx++ % 2 == 0)
                                           ? glm::vec4(0.78f, 0.75f, 0.68f, 1.0f)
                                           : glm::vec4(0.45f, 0.44f, 0.41f, 1.0f));

                    bubble::Renderer::Submit(m_shader.get(), m_vertexArray, transform);
                }

                idx++;
            }
        }
        bubble::Renderer::EndScene();
        // Renderer::Flush();
	}

	void onImGuiRender() override
	{
        if (ImGui::CollapsingHeader("Camera"))
        {
            float rotation = m_camera->getRotation();
            glm::vec3 position = m_camera->getPosition();
            ImGui::InputFloat3("Position", (float*)(&position), 10.0f);
            ImGui::InputFloat("Rotation", (float*)(&rotation), 0.1f);

            m_camera->setPosition(position);
            m_camera->setRotation(rotation);
        }
	}

	void onEvent(bubble::Event& event) override
	{
        bubble::EventDispatcher dispatcher(event);
        dispatcher.dispatch<bubble::KeyPressedEvent>([this](bubble::KeyPressedEvent& event) { return onKeyPressed(event); });
        dispatcher.dispatch<bubble::KeyReleasedEvent>([this](bubble::KeyReleasedEvent& event) { return onKeyReleased(event); });
	}

    bool onKeyPressed(bubble::KeyPressedEvent event)
    {
        const auto& position = m_camera->getPosition();

        const auto& keyEvent = static_cast<const bubble::KeyEvent&>(event);
        switch (keyEvent.getKeyCode())
        {
        case BUBBLE_KEY_LEFT:
            m_camera->setPosition(position - glm::vec3(10.0f, 0.0f, 0.0f));
            return true;

        case BUBBLE_KEY_RIGHT:
            m_camera->setPosition(position + glm::vec3(10.0f, 0.0f, 0.0f));
            return true;

        case BUBBLE_KEY_UP:
            m_camera->setPosition(position - glm::vec3(0.0f, 10.0f, 0.0f));
            return true;

        case BUBBLE_KEY_DOWN:
            m_camera->setPosition(position + glm::vec3(0.0f, 10.0f, 0.0f));
            return true;

        case BUBBLE_KEY_A:
            m_objectPosition.x -= 10.0f;
            return true;

        case BUBBLE_KEY_D:
            m_objectPosition.x += 10.0f;
            return true;

        case BUBBLE_KEY_W:
            m_objectPosition.y -= 10.0f;
            return true;

        case BUBBLE_KEY_S:
            m_objectPosition.y += 10.0f;
            return true;

        default:
            return false;
        }
    }

    bool onKeyReleased(bubble::KeyReleasedEvent& event)
    {
        if (event.getKeyCode() == BUBBLE_KEY_ESCAPE)
        {
            std::exit(0);
            return true;
        }

        return false;
    }


private:
    bubble::Ref<bubble::Shader> m_shader;
    bubble::Ref<bubble::VertexBuffer> m_vertexBuffer;
    bubble::Ref<bubble::IndexBuffer> m_indexBuffer;
    bubble::Ref<bubble::VertexArray> m_vertexArray;
    std::unique_ptr<bubble::Camera> m_camera;

    glm::vec3 m_objectPosition = glm::vec3{ 400.0f, 100.0f, 0.0f };
    const float m_rectangleSize = 50.0f;
};

class Sandbox : public bubble::Application
{
public:
	Sandbox()
	{
		pushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

bubble::Application* bubble::CreateApplication()
{
	return new Sandbox();
}
