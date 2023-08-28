#include "Sandbox2D.h"

#include "Bamboozle/Hash.h"
#include "Helpers.h"

#include <imgui.h>

Sandbox2DLayer::Sandbox2DLayer()
    : Layer("Sandbox2DLayer")
{
}

void Sandbox2DLayer::onAttach()
{
    auto& window = bbzl::Application::GetInstance().getWindow();

    m_camera = std::make_unique<bbzl::OrthographicCamera>(window.getWidth(), window.getHeight());

	bbzl::ResourceSystem rs;
    rs.loadBundle(bbzl::Application::GetInstance().getResourceDirectory() / "common/desc.json");

	m_sprite1 = rs.getSprite(1);
	m_sprite2 = rs.getSprite(2);
	m_sprite3 = rs.getSprite(3);
}

void Sandbox2DLayer::onDetach()
{
}

void Sandbox2DLayer::onUpdate(float dt)
{
}

void Sandbox2DLayer::onRender()
{
	bbzl::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    bbzl::RenderCommand::Clear();

    bbzl::Renderer2D::BeginScene(m_camera.get());

	// m_sprite1->draw();

    bbzl::Renderer2D::EndScene();
}

void Sandbox2DLayer::onImGuiRender()
{
}

void Sandbox2DLayer::onEvent(bbzl::Event& event)
{
    // m_cameraController->onEvent(event);

    bbzl::EventDispatcher dispatcher(event);
    dispatcher.dispatch<bbzl::KeyReleasedEvent>([this](bbzl::KeyEvent& e) { return onKeyEvent(e); });
    dispatcher.dispatch<bbzl::WindowResizeEvent>([this](bbzl::WindowResizeEvent& e) {
        m_camera->setSize(e.getWidth(), e.getHeight());
        return true;
    });
}

bool Sandbox2DLayer::onKeyEvent(const bbzl::KeyEvent& event)
{
    if (event.getKeyCode() == BBZL_KEY_ESCAPE)
    {
        bbzl::Application::GetInstance().quit();
        return true;
    }

    return false;
}
