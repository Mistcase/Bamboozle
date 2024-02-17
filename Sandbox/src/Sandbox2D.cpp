#include "Sandbox2D.h"

#include "Bamboozle/Hash.h"
#include "Bamboozle/Sprite.h"
#include "Helpers.h"

#include <imgui.h>

using namespace bbzl;

Sandbox2DLayer::Sandbox2DLayer()
    : Layer("Sandbox2DLayer")
{
}

void Sandbox2DLayer::onAttach()
{
    auto& window = bbzl::Application::GetInstance().getWindow();

    m_camera = std::make_unique<bbzl::OrthographicCamera>(window.getWidth(), window.getHeight());
    rs.loadBundle((bbzl::Application::GetInstance().getResourceDirectory() / "common/desc.json").generic_string());

	m_sprite1 = rs.getSprite("path_to_sprite_1"_hash);
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

	m_sprite1->draw({0, 0}, { 1.0f, 1.0f }, 0.0f);

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
