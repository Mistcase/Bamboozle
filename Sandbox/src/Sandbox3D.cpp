#include "Sandbox3D.h"

#include "Helpers.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui.h>

Sandbox3DLayer::Sandbox3DLayer()
    : Layer("Sandbox3DLayer")
{
}

void Sandbox3DLayer::onAttach()
{
    auto& window = butterfly::Application::GetInstance().getWindow();

	m_camera = std::make_unique<butterfly::PerspectiveCamera>(glm::radians(45.0f), (float)window.getWidth() / window.getHeight(), 0.5f, 40.0f);
	m_camera->setPosition({ 0.0f, 0.0f, 5.0f });

	m_cameraController = std::make_unique<butterfly::PerspectiveCameraController>(m_camera.get());

	m_teapot = std::make_unique<butterfly::Object3D>(helpers::MakePath("objects/teapot.obj"));
	m_teapot->setPosition({0.0f, 0.0f, 0.0f});

	m_ka = 0.3f;
	m_kd = 0.2f;
	m_ambientColor = { 1.0f, 1.0f, 1.0f };
}

void Sandbox3DLayer::onDetach()
{
}

void Sandbox3DLayer::onUpdate(float dt)
{
	static float angle = 0.0f;
	if (butterfly::Input::IsKeyPressed(BUTTERFLY_KEY_LEFT))
	{
		angle += dt;
		m_teapot->setRotation(angle, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (butterfly::Input::IsKeyPressed(BUTTERFLY_KEY_RIGHT))
	{
		angle -= dt;
		m_teapot->setRotation(angle, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	m_cameraController->onUpdate(dt);

	butterfly::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });
	butterfly::RenderCommand::Clear();

	butterfly::Renderer::BeginScene(m_camera.get());

	static_cast<butterfly::OpenGLShader*>(butterfly::Renderer2D::Shader())->setUniform1f("u_ka", m_ka);
	static_cast<butterfly::OpenGLShader*>(butterfly::Renderer2D::Shader())->setUniform3f("u_ambientColor", m_ambientColor);
	static_cast<butterfly::OpenGLShader*>(butterfly::Renderer2D::Shader())->setUniform1f("u_kd", m_kd);

	m_phase += dt;
	const glm::vec3 lightDirection{ cos(m_phase), 0.0f, sin(m_phase) };
	static_cast<butterfly::OpenGLShader*>(butterfly::Renderer2D::Shader())->setUniform3f("u_lightDirection", -lightDirection);

	butterfly::Renderer::DrawObject(m_teapot);
    butterfly::Renderer::EndScene();
}

void Sandbox3DLayer::onImGuiRender()
{
}

void Sandbox3DLayer::onEvent(butterfly::Event& event)
{
    m_cameraController->onEvent(event);

    butterfly::EventDispatcher dispatcher(event);
    dispatcher.dispatch<butterfly::KeyReleasedEvent>([this](butterfly::KeyEvent& e){ return onKeyEvent(e); });
    dispatcher.dispatch<butterfly::WindowResizeEvent>([this](butterfly::WindowResizeEvent& e)
    {
		// m_camera->onWindowsSizeChanged();
        return true;
    });
}

bool Sandbox3DLayer::onKeyEvent(const butterfly::KeyEvent& event)
{
    if (event.getKeyCode() == BUTTERFLY_KEY_ESCAPE)
    {
        butterfly::Application::GetInstance().quit();
        return true;
    }

    return false;
}
