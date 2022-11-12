#include <Bubble.h>

#include "ImGui/imgui.h"

class ExampleLayer : public bubble::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
        auto& window = bubble::Application::GetInstance().getWindow();
        m_camera = std::make_unique<bubble::Camera>(200.0f, 200.0f);
        m_camera->setPosition({ 540.0f, 260.0f, 0.0f });
        // m_camera->setRotation(M_PI_4);

        m_vertexArray.reset(bubble::VertexArray::Create());
		float vertices[] = {
            590.0f, 410.0f, 0.0f,
            690.0f, 410.0f, 0.0f,
            640.0f, 310.0f, 0.0f,
		};

		unsigned int indices[] = { 0, 1, 2 };
        m_indexBuffer.reset(bubble::IndexBuffer::Create(indices, std::size(indices)));
        m_vertexArray.reset(bubble::VertexArray::Create());
        auto vertexBuffer = std::shared_ptr<bubble::VertexBuffer>(bubble::VertexBuffer::Create(vertices, sizeof(vertices)));
        vertexBuffer->setLayout({
                { bubble::ShaderDataType::Float3, "a_Position" }
            });

        m_vertexArray->addVertexBuffer(vertexBuffer);
        m_vertexArray->setIndexBuffer(m_indexBuffer);

        std::string vertexSource = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;

        uniform mat4 u_VP;
        out vec4 v_Color;

        void main()
        {
            v_Color = vec4(0.8, 0.0, 0.0, 1.0);
            gl_Position = u_VP * vec4(a_Position, 1.0);
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

        m_shader = std::make_unique<bubble::Shader>(vertexSource, fragmentSource);
	}

	void onUpdate(float dt) override
	{
        BUBBLE_CLIENT_TRACE("{0}s", dt);

        bubble::Renderer::BeginScene(m_camera.get(), m_shader.get());
        {
            bubble::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
            bubble::RenderCommand::Clear();

            bubble::Renderer::Submit(m_vertexArray);
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
    std::shared_ptr<bubble::Shader> m_shader;
    std::shared_ptr<bubble::VertexBuffer> m_vertexBuffer;
    std::shared_ptr<bubble::IndexBuffer> m_indexBuffer;
    std::shared_ptr<bubble::VertexArray> m_vertexArray;
    std::unique_ptr<bubble::Camera> m_camera;

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
