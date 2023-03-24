#include "Scene.h"

#include "Butterfly/Application.h"
#include "Butterfly/Object3D.h"
#include "Butterfly/Renderer/Renderer.h"
#include "Butterfly/Renderer/UniformBuffer.h"
#include "Butterfly/Renderer/VertexArray.h"
#include "Butterfly/butterflypch.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace
{
    constexpr size_t MaxLightsSimultaneously = 8;

    struct PointLightsBuffer
    {
        struct PointLight
        {
            glm::vec3 position;
            unsigned char __unused1[4];
            glm::vec3 intensity;
            float radius;
            float linearRatio;
            float quadraticRatio;
            unsigned char __unused2[8];
        };

        uint32_t used;
        unsigned char __unused1[12];
        PointLight lights[MaxLightsSimultaneously];
    };

} // namespace

namespace butterfly
{
    Scene::Scene()
        : m_pointLightsBuffer(UniformBuffer::Create(sizeof(PointLightsBuffer)))
    {
        auto& window = butterfly::Application::GetInstance().getWindow();
        m_camera = std::make_unique<butterfly::PerspectiveCamera>(glm::radians(45.0f), (float)window.getWidth() / window.getHeight(), 0.5f, 100.0f);
        m_cameraController = std::make_unique<butterfly::PerspectiveCameraController>(m_camera.get());

        // TODO: do smth with such numeric literals
        Renderer::Shader()->bindUniformBlock("PointLights", 2);
        m_pointLightsBuffer->bind(2);
    }

    void Scene::update(float dt)
    {
        m_cameraController->onUpdate(dt);

        for (auto& light : m_lights)
            light.update(dt);

        for (auto& object : m_objects)
            object->update(dt);
    }

    void Scene::render() const
    {
        Renderer::BeginScene(m_camera.get());

        drawWorldAxes();

        submitLights();
        for (const auto& object : m_objects)
        {
            object->render();
        }

        Renderer::EndScene();
    }

    void Scene::renderImGui()
    {
    }

    void Scene::drawWorldAxes() const
    {
        const glm::vec3 origin{ 0.0f, 0.0f, 0.0f };

        RenderCommand::SetLineWidth(5);

        Renderer::DrawLine({ origin, { 10.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } });
        Renderer::DrawLine({ origin, { 0.0f, 10.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } });
        Renderer::DrawLine({ origin, { 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } });

        RenderCommand::SetLineWidth(10);
        Renderer::DrawLine({ origin, m_lights.front().getPosition(), { 1.0f, 1.0f, 1.0f, 1.0f } });
    }

    void Scene::submitLights() const
    {
        // Point lights
        assert(m_lights.size() < MaxLightsSimultaneously);

        static PointLightsBuffer buffer;
        buffer.used = m_lights.size();
        for (size_t i = 0; i < buffer.used; i++)
        {
            auto light = m_lights[i];
            auto& bufferLight = buffer.lights[i];

            bufferLight.position = light.getPosition();
            bufferLight.intensity = light.getIntensity();
            bufferLight.radius = light.getRadius();

            const auto attenuation = light.getAttenuation();
            bufferLight.linearRatio = attenuation.linearRatio;
            bufferLight.quadraticRatio = attenuation.quadraticRatio;
        }

        const auto bufferSize = offsetof(PointLightsBuffer, lights) + buffer.used * sizeof(PointLightsBuffer::PointLight);
        m_pointLightsBuffer->bind(2);
        m_pointLightsBuffer->submit(&buffer, bufferSize);
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
