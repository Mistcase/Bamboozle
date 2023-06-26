#include "Sandbox2D.h"

#include "Helpers.h"
#include <imgui.h>

Sandbox2DLayer::Sandbox2DLayer()
    : Layer("Sandbox2DLayer")
{
}

void Sandbox2DLayer::onAttach()
{
    auto& window = bbzl::Application::GetInstance().getWindow();

    m_camera = std::make_unique<bbzl::Camera>(window.getWidth(), window.getHeight());
    m_cameraController = std::make_unique<bbzl::CameraController>(m_camera.get());

    m_texture = bbzl::Texture2D::Create(helpers::MakePath("textures/Checkerboard.png").string());
    m_texture2 = bbzl::Texture2D::Create(helpers::MakePath("textures/smoke.png").string());
}

void Sandbox2DLayer::onDetach()
{
}

void Sandbox2DLayer::onUpdate(float dt)
{
    m_cameraController->onUpdate(dt);

    bbzl::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    bbzl::RenderCommand::Clear();

    bbzl::Renderer2D::BeginScene(m_camera.get());
    bbzl::Renderer2D::DrawQuad({ 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f }, glm::radians(45.0f), { 1.0f, 0.0f, 0.0f, 1.0f }, m_texture);
    bbzl::Renderer2D::DrawQuad({ 0.5f, 0.5f, -1.0f }, { 1.0f, 1.0f }, 0.0f, { 0.0f, 0.0f, 1.0f, 1.0f }, m_texture2);
    // bbzl::Renderer2D::DrawQuad({ -300.0f, -300.0f, -z }, { 250.0f, 250.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });

    bbzl::Renderer2D::EndScene();
}

void Sandbox2DLayer::onImGuiRender()
{
}

void Sandbox2DLayer::onEvent(bbzl::Event& event)
{
    m_cameraController->onEvent(event);

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
