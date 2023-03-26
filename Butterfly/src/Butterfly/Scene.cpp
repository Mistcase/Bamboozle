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
    constexpr size_t MaxPointLightsSimultaneously = 8;
    constexpr size_t MaxDirectionalLightsSimultaneously = 4;

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
        PointLight lights[MaxPointLightsSimultaneously];
    };

    struct DirectionalLightsBuffer
    {
        struct DirectionalLight
        {
            glm::vec3 intensity;
			unsigned char __unused1[4];
            glm::vec3 direction;
			unsigned char __unused2[4];
        };

        uint32_t used;
        unsigned char __unused1[12];
        DirectionalLight lights[MaxDirectionalLightsSimultaneously];
    };

} // namespace

namespace butterfly
{
    Scene::Scene()
        : m_pointLightsBuffer(UniformBuffer::Create(sizeof(PointLightsBuffer)))
        , m_directionalLightsBuffer(UniformBuffer::Create(sizeof(DirectionalLightsBuffer)))
    {
        auto& window = butterfly::Application::GetInstance().getWindow();
        m_camera = std::make_unique<butterfly::PerspectiveCamera>(glm::radians(45.0f), (float)window.getWidth() / window.getHeight(), 0.5f, 100.0f);
        m_cameraController = std::make_unique<butterfly::PerspectiveCameraController>(m_camera.get());

        // TODO: do smth with such numeric literals
        Renderer::Shader()->bindUniformBlock("PointLights", 2);
        m_pointLightsBuffer->bind(2);

        Renderer::Shader()->bindUniformBlock("DirectionalLights", 3);
        m_directionalLightsBuffer->bind(3);
    }

    void Scene::update(float dt)
    {
        m_cameraController->onUpdate(dt);

        for (auto& light : m_pointLights)
            light.update(dt);

        for (auto& light : m_directionalLights)
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

    void Scene::drawWorldAxes() const
    {
        const glm::vec3 origin{ 0.0f, 0.0f, 0.0f };

        RenderCommand::SetLineWidth(5);

        Renderer::DrawLine({ origin, { 10.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } });
        Renderer::DrawLine({ origin, { 0.0f, 10.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } });
        Renderer::DrawLine({ origin, { 0.0f, 0.0f, 10.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } });

        RenderCommand::SetPointSize(20);
        Renderer::DrawPoint({ 0.0, 5.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 0.7f });
    }

    void Scene::submitLights() const
    {
        // Point lights
        assert(m_directionalLights.size() < MaxPointLightsSimultaneously);

        static PointLightsBuffer pbuffer;
        pbuffer.used = m_pointLights.size();
        for (size_t i = 0; i < pbuffer.used; i++)
        {
            const auto& light = m_pointLights[i];
            auto& pbufferLight = pbuffer.lights[i];

            pbufferLight.position = light.getPosition();
            pbufferLight.intensity = light.getIntensity();
            pbufferLight.radius = light.getRadius();

            const auto attenuation = light.getAttenuation();
            pbufferLight.linearRatio = attenuation.linearRatio;
            pbufferLight.quadraticRatio = attenuation.quadraticRatio;
        }
        const auto pbufferSize = offsetof(PointLightsBuffer, lights) + pbuffer.used * sizeof(PointLightsBuffer::PointLight);
        m_pointLightsBuffer->bind(2);
        m_pointLightsBuffer->submit(&pbuffer, pbufferSize);

        static DirectionalLightsBuffer dbuffer;
        dbuffer.used = m_directionalLights.size();
        for (size_t i = 0; i < dbuffer.used; i++)
        {
            const auto& light = m_directionalLights[i];
            auto& dbufferLight = dbuffer.lights[i];

            dbufferLight.intensity = light.getIntensity();
            dbufferLight.direction = light.getDirection();
        }
        const auto dbufferSize = offsetof(DirectionalLightsBuffer, lights) + dbuffer.used * sizeof(DirectionalLightsBuffer::DirectionalLight);
        m_directionalLightsBuffer->bind(3);
        m_directionalLightsBuffer->submit(&dbuffer, dbufferSize);
    }

    const Scene::PointLights& Scene::getPointLights() const
    {
        return m_pointLights;
    }

    const Scene::DirectionalLights& Scene::getDirectionalLights() const
    {
        return m_directionalLights;
    }

    const Scene::Objects Scene::getObjects() const
    {
        return m_objects;
    }

} // namespace butterfly
