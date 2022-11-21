#include "EditorLayer.h"

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
	}

	void onUpdate(float dt) override
	{
        m_cameraController->onUpdate(dt);
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

class Editor : public bubble::Application
{
public:
	Editor()
        : bubble::Application("Bubble editor")
	{
        pushLayer(new EditorLayer());
	}

	~Editor()
	{
	}
};

bubble::Application* bubble::CreateApplication()
{
	return new Editor();
}
