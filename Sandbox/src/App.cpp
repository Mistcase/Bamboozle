#include "Sandbox2D.h"

#include "Bubble/CameraController.h"
#include "Bubble/Renderer/Shaders.h"
#include <Bubble.h>
#include <Bubble/EntryPoint.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include <ImGui/imgui.h>
#include <glm/ext/matrix_transform.hpp>

class ExampleLayer : public bubble::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
        auto& window = bubble::Application::GetInstance().getWindow();
        m_camera = std::make_unique<bubble::Camera>(window.getWidth(), window.getHeight());
        m_cameraController = std::make_unique<bubble::CameraController>(m_camera.get());
        m_camera->setPosition(glm::vec3(0.0f));

        m_shaderManager = bubble::Shaders::Create();
        m_shader = m_shaderManager->createFromFile("assets\\shaders\\default.glsl");

		// float vertices[] = {
        //     0.0f,            0.0f,            0.0f,
        //     m_rectangleSize, 0.0f,            0.0f,
        //     m_rectangleSize, m_rectangleSize, 0.0f,
        //     0.0f,            m_rectangleSize, 0.0f,
		// };

		// unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
        // m_indexBuffer = bubble::IndexBuffer::Create(indices, std::size(indices));
        // m_vertexArray = bubble::VertexArray::Create();
        // auto vertexBuffer = bubble::Ref<bubble::VertexBuffer>(bubble::VertexBuffer::Create(vertices, sizeof(vertices)));
        // vertexBuffer->setLayout({
        //         { bubble::ShaderDataType::Float3, "a_Position" }
        //     });

        // m_vertexArray->addVertexBuffer(vertexBuffer);
        // m_vertexArray->setIndexBuffer(m_indexBuffer);
	}

	void onUpdate(float dt) override
	{
        m_cameraController->onUpdate(dt);

        bubble::Renderer::BeginScene(m_camera.get());
        {
            bubble::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
            bubble::RenderCommand::Clear();

            auto idx = 0;
            for (int x = 0; x < 6; x++)
            {
                for (int y = 0; y < 6; y++)
                {
                    const auto o = 1.1f * m_rectangleSize;
                    const auto transform = glm::translate(glm::mat4(1.0f), m_objectPosition + glm::vec3(o * x, o * y, 0.0f));

                    static_cast<const bubble::OpenGLShader*>(m_shader)->setUniform4f("u_Color", (idx++ % 2 == 0)
                                                                                     ? glm::vec4(0.78f, 0.75f, 0.68f, 1.0f)
                                                                                     : glm::vec4(0.45f, 0.44f, 0.41f, 1.0f));

                    bubble::Renderer::Submit(m_shader, m_vertexArray, transform);
                }

                idx++;
            }

            idx = 0;
            for (int x = 0; x < 6; x++)
            {
                for (int y = 0; y < 6; y++)
                {
                    const auto o = 1.1f * m_rectangleSize;
                    const auto transform = glm::translate(glm::mat4(1.0f), glm::vec3(500, 500, 0) + glm::vec3(o * x, o * y, 0.0f));

                    static_cast<const bubble::OpenGLShader*>(m_shader)->setUniform4f("u_Color", (idx++ % 2 == 0)
                                                                                     ? glm::vec4(0.78f, 0.75f, 0.68f, 1.0f)
                                                                                     : glm::vec4(0.45f, 0.44f, 0.41f, 1.0f));

                    bubble::Renderer::Submit(m_shader, m_vertexArray, transform);
                }

                idx++;
            }
        }

        bubble::Renderer::EndScene();
	}

	void onImGuiRender() override
	{
	}

	void onEvent(bubble::Event& event) override
	{
        m_cameraController->onEvent(event);

        bubble::EventDispatcher dispatcher(event);
        dispatcher.dispatch<bubble::KeyReleasedEvent>([this](bubble::KeyReleasedEvent& event) { return onKeyReleased(event); });
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
    std::shared_ptr<bubble::Shaders> m_shaderManager;
    bubble::Shader* m_shader;

    bubble::Ref<bubble::VertexBuffer> m_vertexBuffer;
    bubble::Ref<bubble::IndexBuffer> m_indexBuffer;
    bubble::Ref<bubble::VertexArray> m_vertexArray;
    std::unique_ptr<bubble::Camera> m_camera;
    std::unique_ptr<bubble::CameraController> m_cameraController;

    bubble::Ref<bubble::Shader> m_textureShader;
    bubble::Ref<bubble::VertexArray> m_textureVA;
    bubble::Ref<bubble::Texture> m_texture;
    bubble::Ref<bubble::Texture> m_textureSmoke;

    glm::vec3 m_objectPosition = glm::vec3{ -275.0f, -275.0f, 0.0f };
    const float m_rectangleSize = 50.0f;
};

class Sandbox : public bubble::Application
{
public:
	Sandbox()
	{
		// pushLayer(new ExampleLayer());
        pushLayer(new Sandbox2DLayer());
	}

	~Sandbox()
	{
	}
};

bubble::Application* bubble::CreateApplication()
{
	return new Sandbox();
}
