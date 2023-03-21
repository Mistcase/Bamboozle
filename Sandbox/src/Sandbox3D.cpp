#include "Sandbox3D.h"

#include "Butterfly/Renderer/Skybox.h"
#include "Helpers.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui.h>

Sandbox3DLayer::Sandbox3DLayer()
    : Layer("Sandbox3DLayer")
{
}

void Sandbox3DLayer::onAttach()
{
	m_objects.push_back(std::make_shared<butterfly::SkyBox>(helpers::MakePath("objects/sphere.obj"), helpers::MakePath("textures/sky.jpeg"), m_camera.get()));
	m_skybox = m_objects.back().get();
	m_skybox->setScale({ 50.0f, 50.0f, 50.0f });

	m_objects.emplace_back(std::make_shared<butterfly::Object3D>(helpers::MakePath("objects/teapot.obj")));
	m_teapot = m_objects.back().get();

	m_objects.emplace_back(std::make_shared<butterfly::Object3D>(helpers::MakePath("objects/lamp.obj")));
	m_objects.back()->setPosition({ 10.0f, 0.0f, 0.0f }); // Barrrel doesnt work properly!!!

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
	switch (event.getKeyCode())
	{
	case BUTTERFLY_KEY_ESCAPE:
		butterfly::Application::GetInstance().quit();
		return true;

	case BUTTERFLY_KEY_LEFT:
		m_teapot->setPosition(m_teapot->getPosition() - glm::vec3{ 1.0f, 0.0f, 0.0f });
		return true;

	case BUTTERFLY_KEY_RIGHT:
		m_teapot->setPosition(m_teapot->getPosition() + glm::vec3{ 1.0f, 0.0f, 0.0f });
		return true;

	case BUTTERFLY_KEY_UP:
		m_teapot->setPosition(m_teapot->getPosition() + glm::vec3{ 0.0f, 1.0f, 0.0f });
		return true;

	case BUTTERFLY_KEY_DOWN:
		m_teapot->setPosition(m_teapot->getPosition() - glm::vec3{ 0.0f, 1.0f, 0.0f });
		return true;

	case BUTTERFLY_KEY_EQUAL:
		m_teapot->setScale(m_teapot->getScale() + glm::vec3(0.5f, 0.5f, 0.5f));
		return true;

	case BUTTERFLY_KEY_MINUS:
		m_teapot->setScale(m_teapot->getScale() - glm::vec3(0.5f, 0.5f, 0.5f));
		return true;
	}

    return false;
}
