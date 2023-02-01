#include "Sandbox2D.h"

#include "Helpers.h"

#include <imgui.h>

Sandbox2DLayer::Sandbox2DLayer()
    : Layer("Sandbox2DLayer")
{
}

void Sandbox2DLayer::onAttach()
{
    auto& window = butterfly::Application::GetInstance().getWindow();

    m_camera = std::make_unique<butterfly::Camera>(window.getWidth(), window.getHeight());
    m_cameraController = std::make_unique<butterfly::CameraController>(m_camera.get());

    m_texture = butterfly::Texture2D::Create(helpers::MakePath("textures/Checkerboard.png").string());
    m_texture2 = butterfly::Texture2D::Create(helpers::MakePath("textures/smoke.png").string());
}

void Sandbox2DLayer::onDetach()
{
}

void Sandbox2DLayer::onUpdate(float dt)
{
    m_cameraController->onUpdate(dt);

    butterfly::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    butterfly::RenderCommand::Clear();

    butterfly::Renderer2D::BeginScene(m_camera.get());
    butterfly::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 250.0f, 250.0f }, glm::radians(45.0f), { 1.0f, 0.0f, 0.0f, 1.0f }, m_texture);
    butterfly::Renderer2D::DrawQuad({ 300.0f, 300.0f, -0.1f }, { 250.0f, 250.0f }, 0.0f, { 0.0f, 0.0f, 1.0f, 1.0f }, m_texture2 );
    butterfly::Renderer2D::DrawQuad({ -300.0f, -300.0f, -0.1f }, { 250.0f, 250.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });

    butterfly::Renderer2D::EndScene();
}

void Sandbox2DLayer::onImGuiRender()
{
}

void Sandbox2DLayer::onEvent(butterfly::Event& event)
{
    m_cameraController->onEvent(event);

    butterfly::EventDispatcher dispatcher(event);
    dispatcher.dispatch<butterfly::KeyReleasedEvent>([this](butterfly::KeyEvent& e){ return onKeyEvent(e); });
    dispatcher.dispatch<butterfly::WindowResizeEvent>([this](butterfly::WindowResizeEvent& e)
    {
        m_camera->setSize(e.getWidth(), e.getHeight());
        return true;
    });
}

bool Sandbox2DLayer::onKeyEvent(const butterfly::KeyEvent& event)
{
    if (event.getKeyCode() == BUTTERFLY_KEY_ESCAPE)
    {
        butterfly::Application::GetInstance().quit();
        return true;
    }

    return false;
}
