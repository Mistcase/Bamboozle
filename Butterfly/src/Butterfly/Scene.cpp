#include "Butterfly/butterflypch.h"
#include "Scene.h"

#include "Butterfly/Application.h"
#include "Butterfly/Object3D.h"
#include "Butterfly/DirectionalLight.h"
#include "Butterfly/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace butterfly
{
    Scene::Scene()
    {
        auto& window = butterfly::Application::GetInstance().getWindow();

       	m_camera = std::make_unique<butterfly::PerspectiveCamera>(glm::radians(45.0f), (float)window.getWidth() / window.getHeight(), 0.5f, 40.0f);
        m_camera->setPosition({ 0.0f, 0.0f, 20.0f });

        m_cameraController = std::make_unique<butterfly::PerspectiveCameraController>(m_camera.get());
    }

    void Scene::update(float dt)
    {
        test(dt);

        m_cameraController->onUpdate(dt);

        for (auto& light : m_lights)
            light.update(dt);

        for (auto& object : m_objects)
            object.update(dt);
    }

    void Scene::render() const
    {
        Renderer::BeginScene(m_camera.get());

        submitLights();
        for (auto& object : m_objects)
        {
            object.render();
        }

        Renderer::EndScene();
    }

    void Scene::renderImGui()
    {

    }

    void Scene::test(float dt)
    {
        static float phase = 0.0f;

        static_cast<butterfly::OpenGLShader*>(butterfly::Renderer::Shader())->setUniform1f("u_ka", 0.12f);
        static_cast<butterfly::OpenGLShader*>(butterfly::Renderer::Shader())->setUniform1f("u_kd", 0.3f);
        static_cast<butterfly::OpenGLShader*>(butterfly::Renderer::Shader())->setUniform1f("u_ks", 1.0f);
        static_cast<butterfly::OpenGLShader*>(butterfly::Renderer::Shader())->setUniform1f("u_a", 20.0f);

        phase += dt;
        const glm::vec3 lightDirection{ cos(phase), 0.0f, sin(phase) };
        m_lights.back().setDirection(-lightDirection);
    }

    void Scene::submitLights() const
    {
        const auto size = m_lights.size();
        static_cast<const butterfly::OpenGLShader*>(Renderer::Shader())->setUniform1i("u_DirectionalLightCount", size);

        for (size_t i = 0; i < size; i++)
        {
            const auto& light = m_lights[i];

            // Temporary OpenGL shader only
            const auto lightName = "u_DirectionalLights[" + std::to_string(i) + "]";

            static_cast<const butterfly::OpenGLShader*>(Renderer::Shader())->setUniform3f(lightName + ".intensity", light.getIntensity());
            static_cast<const butterfly::OpenGLShader*>(Renderer::Shader())->setUniform3f(lightName + ".position", light.getPosition());
            static_cast<const butterfly::OpenGLShader*>(Renderer::Shader())->setUniform3f(lightName + ".direction", light.getDirection());
        }
    }

    const Scene::Lights& Scene::getLights() const
    {
        return m_lights;
    }

    const Scene::Objects Scene::getObjects() const
    {
        return m_objects;
    }

} // namespace butterfly
