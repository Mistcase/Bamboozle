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
    m_objects.emplace_back(helpers::MakePath("objects/teapot.obj"));
    m_objects.back().setPosition({0.0f, 0.0f, 0.0f});

    m_lights.emplace_back(glm::vec3{ 0.0f, 0.6f, 0.0f }, glm::vec3{ 0.0f, 0.0f, 5.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f });
    m_lights.emplace_back(glm::vec3{ 0.5f, 0.0f, 0.0f }, glm::vec3{ 0.0f, 0.0f, 5.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f }); // Is OpenGL righthanded
}

void Sandbox3DLayer::onDetach()
{
}

void Sandbox3DLayer::onUpdate(float dt)
{
    Scene::update(dt);
    Scene::render();
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
