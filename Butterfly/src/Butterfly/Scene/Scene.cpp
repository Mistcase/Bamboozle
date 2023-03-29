#include "Butterfly/Renderer/Material.h"
#include "Butterfly/Renderer/Mesh.h"
#include "Butterfly/Scene/Components.h"
#include "Butterfly/butterflypch.h"
#include "Scene.h"

#include "Butterfly/Application.h"
#include "Butterfly/Renderer/Renderer.h"
#include "Butterfly/Renderer/UniformBuffer.h"
#include "Butterfly/Renderer/VertexArray.h"
#include "Butterfly/Transformable.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "Butterfly/KeyCodes.h"

#include <glm/glm.hpp>

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
        // TODO: do smth with such numeric literals
        Renderer::Shader()->bindUniformBlock("PointLights", 2);
        m_pointLightsBuffer->bind(2);

        Renderer::Shader()->bindUniformBlock("DirectionalLights", 3);
        m_directionalLightsBuffer->bind();
    }

	Scene::~Scene()
	{
	}

	Entity Scene::createEntity(const std::string& name)
	{
        auto handle = m_registry.create();
		m_registry.emplace<TagComponent>(handle, name);
        m_registry.emplace<TransformComponent>(handle);

		return { handle, &m_registry };
	}

    void Scene::setCameraPawn(Entity entity)
    {
        assert(entity.hasComponent<CameraComponent>());
        m_cameraController.possess(entity);
    }

    void Scene::update(float dt)
    {
		updateTransforms();
        m_cameraController.update(dt);
    }

    void Scene::render() const
    {
		butterfly::RenderCommand::Clear();
        Renderer::BeginScene(&m_cameraController);

        drawWorldAxes();

        // Submit lights before meshes
        submitLights();
        submitMeshes();

        Renderer::EndScene();
    }

    void Scene::onEvent(Event& event)
    {
        // m_cameraController.onEvent(event);
    }

	void Scene::updateTransforms()
	{
		m_registry.view<TransformComponent>().each([](auto handle, auto& transformComponent)
        {
            transformComponent.updateWorldTransform();
        });
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

    void Scene::submitMeshes() const
    {
        for (auto &&[entity, mesh, material, transform] : m_registry.group<MeshComponent>(entt::get<MaterialComponent, TransformComponent>).each())
        {
            static_cast<OpenGLShader*>(Renderer::Shader())->setUniformMat4("u_Transform", transform.getWorldTransform());

            material.apply();
            mesh.draw();
        }
    }

    void Scene::submitLights() const
    {
        auto pointLights = m_registry.group<PointLightComponent>(entt::get<TransformComponent>);
        assert(pointLights.size() < MaxPointLightsSimultaneously);

        auto directionalLights = m_registry.group<DirectionalLightComponent>(entt::get<TransformComponent>);
        assert(directionalLights.size() < MaxDirectionalLightsSimultaneously);

        size_t idx = 0;
        static PointLightsBuffer pbuffer;
        pbuffer.used = pointLights.size();
        for (auto&& [handle, light, transform] : pointLights.each())
        {
            auto& pbufferLight = pbuffer.lights[idx];

            pbufferLight.position = transform.getPosition();
            pbufferLight.intensity = light.intensity;
            pbufferLight.radius = light.radius;

            const auto attenuation = light.attenuation;
            pbufferLight.linearRatio = attenuation.linearRatio;
            pbufferLight.quadraticRatio = attenuation.quadraticRatio;
            idx++;
        }
        const auto pbufferSize = offsetof(PointLightsBuffer, lights) + pbuffer.used * sizeof(PointLightsBuffer::PointLight);
        m_pointLightsBuffer->bind(2);
        m_pointLightsBuffer->submit(&pbuffer, pbufferSize);
        idx = 0;

        static DirectionalLightsBuffer dbuffer;
        dbuffer.used = directionalLights.size();
        for (auto&& [handle, light, transform] : directionalLights.each())
        {
            auto& dbufferLight = dbuffer.lights[idx];

            dbufferLight.intensity = light.intensity;
            dbufferLight.direction = light.direction;
            idx++;
        }
        const auto dbufferSize = offsetof(DirectionalLightsBuffer, lights) + dbuffer.used * sizeof(DirectionalLightsBuffer::DirectionalLight);
        m_directionalLightsBuffer->bind(3);
        m_directionalLightsBuffer->submit(&dbuffer, dbufferSize);
    }

} // namespace butterfly
