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
    m_camera->setPosition({ 7.0f, 8.0f, 10.0f });

    m_objects.push_back(std::make_shared<butterfly::SkyBox>(helpers::MakePath("objects/sphere.obj"), helpers::MakePath("textures/sky.jpeg"), m_camera.get()));
    m_skybox = m_objects.back().get();
    m_skybox->setScale({ 50.0f, 50.0f, 50.0f });

    m_objects.emplace_back(std::make_shared<butterfly::Object3D>(helpers::MakePath("objects/scene.obj")));
    auto scene = m_objects.back();

    m_pointLights.emplace_back(glm::vec3{ 0.0f, 1.0f, 0.0f }, 2.5f, glm::vec3{ 0.0f, 0.5f, 0.0f });
    m_pointLights.emplace_back(glm::vec3{ 1.0f, 0.0f, 0.0f }, 2.0f, glm::vec3{ -1.5f, 1.5f, 0.0f });
	m_directionalLights.emplace_back(glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec3{ 0.0f, -1.0f, 0.0f });

    std::vector<butterfly::Ref<butterfly::Texture>> textures{ butterfly::Texture2D::Create(helpers::MakePath("textures/wall.jpeg").generic_string()) };
    auto wallMaterial = butterfly::Material::Create(butterfly::Renderer::Shader(), { 0.12f, 0.3f, 1.0f, 20.0f }, std::move(textures));
    scene->setMaterial(wallMaterial);

    m_objects.emplace_back(std::make_shared<butterfly::Object3D>(helpers::MakePath("objects/barrel.obj")));
    m_barrel = m_objects.back().get();

    auto t1 = butterfly::Texture2D::Create(helpers::MakePath("textures/barrel/varil_low_lambert1_BaseColor.png"));
    auto t2 = butterfly::Texture2D::Create(helpers::MakePath("textures/barrel/varil_low_lambert1_Metallic.png"), butterfly::Texture2D::Format::RED);
    std::vector<butterfly::Ref<butterfly::Texture>> textures2{ t1, t2 };

    m_barrel->setMaterial(butterfly::Material::Create(butterfly::Renderer::Shader(), { 0.12f, 0.3f, 1.0f, 20.0f }, std::move(textures2)));
    m_barrel->setPosition({ 2.0f, 1.0f, 2.0f});
    m_barrel->setScale({ 0.4f, 0.4f, 0.4f });
}

void Sandbox3DLayer::onDetach()
{
}

void Sandbox3DLayer::onUpdate(float dt)
{
	m_directionalLights.back().setDirection(glm::normalize(m_camera->getViewDirection()));

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
    dispatcher.dispatch<butterfly::KeyReleasedEvent>([this](butterfly::KeyEvent& e) { return onKeyEvent(e); });
    dispatcher.dispatch<butterfly::WindowResizeEvent>([this](butterfly::WindowResizeEvent& e) {
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
        return true;

    case BUTTERFLY_KEY_RIGHT:
        return true;

    case BUTTERFLY_KEY_UP:
        m_pointLights.back().setAttenuation({ 0.0f, m_pointLights.back().getAttenuation().quadraticRatio + 0.1f });
        BUTTERFLY_CORE_INFO("Attenuation: {}\n", m_pointLights.back().getAttenuation().quadraticRatio);
        return true;

    case BUTTERFLY_KEY_DOWN:
        m_pointLights.back().setAttenuation({ 0.0f, m_pointLights.back().getAttenuation().quadraticRatio - 0.1f });
        BUTTERFLY_CORE_INFO("Attenuation: {}\n", m_pointLights.back().getAttenuation().quadraticRatio);
        return true;

    case BUTTERFLY_KEY_EQUAL:
        return true;

    case BUTTERFLY_KEY_MINUS:
        return true;

    case BUTTERFLY_KEY_R:
        // Reload default shader
        butterfly::Renderer2D::Destroy();
        butterfly::Renderer2D::Init();
        return true;
    }

    return false;
}
