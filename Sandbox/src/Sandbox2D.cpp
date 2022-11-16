#include "Sandbox2D.h"

#include <ImGui/imgui.h>

Sandbox2DLayer::Sandbox2DLayer()
    : Layer("Sandbox2DLayer")
{
}

void Sandbox2DLayer::onAttach()
{
    auto& window = bubble::Application::GetInstance().getWindow();

    m_camera = std::make_unique<bubble::Camera>(window.getWidth(), window.getHeight());
    m_cameraController = std::make_unique<bubble::CameraController>(m_camera.get());

    m_texture = bubble::Texture2D::Create("assets/Checkerboard.png");
}

void Sandbox2DLayer::onDetach()
{

}

void Sandbox2DLayer::onUpdate(float dt)
{
    m_cameraController->onUpdate(dt);

    bubble::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    bubble::RenderCommand::Clear();

    bubble::Renderer2D::BeginScene(m_camera.get());
    bubble::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, glm::vec2{ 250.0f, 250.0f } * 100.0f, m_texture);

    bubble::Renderer2D::EndScene();
}

void Sandbox2DLayer::onImGuiRender()
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

void Sandbox2DLayer::onEvent(bubble::Event& event)
{
    m_cameraController->onEvent(event);

    if (event.getEventType() == bubble::EventType::WindowResize)
    {
        auto& e = static_cast<bubble::WindowResizeEvent&>(event);
        m_camera->setSize(e.getWidth(), e.getHeight());
    }
}
