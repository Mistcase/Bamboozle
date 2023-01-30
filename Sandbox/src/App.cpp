#include "Sandbox2D.h"

#include "Butterfly/CameraController.h"
#include "Butterfly/Renderer/Shaders.h"
#include <Butterfly.h>
#include <Butterfly/EntryPoint.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include <imgui.h>
#include <glm/ext/matrix_transform.hpp>

class ExampleLayer : public butterfly::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
        auto& window = butterfly::Application::GetInstance().getWindow();
        m_camera = std::make_unique<butterfly::Camera>(window.getWidth(), window.getHeight());
        m_cameraController = std::make_unique<butterfly::CameraController>(m_camera.get());
        m_camera->setPosition(glm::vec3(0.0f));

        m_shaderManager = butterfly::Shaders::Create();
        m_shader = m_shaderManager->createFromFile("assets\\shaders\\default.glsl");

		// float vertices[] = {
        //     0.0f,            0.0f,            0.0f,
        //     m_rectangleSize, 0.0f,            0.0f,
        //     m_rectangleSize, m_rectangleSize, 0.0f,
        //     0.0f,            m_rectangleSize, 0.0f,
		// };

		// unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
        // m_indexBuffer = butterfly::IndexBuffer::Create(indices, std::size(indices));
        // m_vertexArray = butterfly::VertexArray::Create();
        // auto vertexBuffer = butterfly::Ref<butterfly::VertexBuffer>(butterfly::VertexBuffer::Create(vertices, sizeof(vertices)));
        // vertexBuffer->setLayout({
        //         { butterfly::ShaderDataType::Float3, "a_Position" }
        //     });

        // m_vertexArray->addVertexBuffer(vertexBuffer);
        // m_vertexArray->setIndexBuffer(m_indexBuffer);
	}

	void onUpdate(float dt) override
	{
        m_cameraController->onUpdate(dt);

        butterfly::Renderer::BeginScene(m_camera.get());
        {
            butterfly::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
            butterfly::RenderCommand::Clear();

            auto idx = 0;
            for (int x = 0; x < 6; x++)
            {
                for (int y = 0; y < 6; y++)
                {
                    const auto o = 1.1f * m_rectangleSize;
                    const auto transform = glm::translate(glm::mat4(1.0f), m_objectPosition + glm::vec3(o * x, o * y, 0.0f));

                    static_cast<const butterfly::OpenGLShader*>(m_shader)->setUniform4f("u_Color", (idx++ % 2 == 0)
                                                                                     ? glm::vec4(0.78f, 0.75f, 0.68f, 1.0f)
                                                                                     : glm::vec4(0.45f, 0.44f, 0.41f, 1.0f));

                    butterfly::Renderer::Submit(m_shader, m_vertexArray, transform);
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

                    static_cast<const butterfly::OpenGLShader*>(m_shader)->setUniform4f("u_Color", (idx++ % 2 == 0)
                                                                                     ? glm::vec4(0.78f, 0.75f, 0.68f, 1.0f)
                                                                                     : glm::vec4(0.45f, 0.44f, 0.41f, 1.0f));

                    butterfly::Renderer::Submit(m_shader, m_vertexArray, transform);
                }

                idx++;
            }
        }

        butterfly::Renderer::EndScene();
	}

	void onImGuiRender() override
	{
	}

	void onEvent(butterfly::Event& event) override
	{
        m_cameraController->onEvent(event);

        butterfly::EventDispatcher dispatcher(event);
        dispatcher.dispatch<butterfly::KeyReleasedEvent>([this](butterfly::KeyReleasedEvent& event) { return onKeyReleased(event); });
	}

    bool onKeyReleased(butterfly::KeyReleasedEvent& event)
    {
        if (event.getKeyCode() == BUTTERFLY_KEY_ESCAPE)
        {
            std::exit(0);
            return true;
        }

        return false;
    }

private:
    std::shared_ptr<butterfly::Shaders> m_shaderManager;
    butterfly::Shader* m_shader;

    butterfly::Ref<butterfly::VertexBuffer> m_vertexBuffer;
    butterfly::Ref<butterfly::IndexBuffer> m_indexBuffer;
    butterfly::Ref<butterfly::VertexArray> m_vertexArray;
    std::unique_ptr<butterfly::Camera> m_camera;
    std::unique_ptr<butterfly::CameraController> m_cameraController;

    butterfly::Ref<butterfly::Shader> m_textureShader;
    butterfly::Ref<butterfly::VertexArray> m_textureVA;
    butterfly::Ref<butterfly::Texture> m_texture;
    butterfly::Ref<butterfly::Texture> m_textureSmoke;

    glm::vec3 m_objectPosition = glm::vec3{ -275.0f, -275.0f, 0.0f };
    const float m_rectangleSize = 50.0f;
};

class Sandbox : public butterfly::Application
{
public:
	Sandbox()
	{
        pushLayer(new Sandbox2DLayer());
	}

	~Sandbox()
	{
	}
};

butterfly::Application* butterfly::CreateApplication()
{
	return new Sandbox();
}
