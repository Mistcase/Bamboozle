#pragma once

#include "Bamboozle/Core.h"
#include "Bamboozle/Renderer/PerspectiveCamera.h"
#include "Bamboozle/Scene/Entity.h"

#include <vector>

namespace bbzl
{
    class DirectionalLight;
    class UniformBuffer;
    struct TransformComponent;

    class Scene final
    {
    public:
        Scene();
		~Scene();

		Entity createEntity(const std::string& name);
        void setCameraPawn(Entity entity);

        void update(float dt);
        void render() const;

        void onEvent(Event& event);

    private:
        void createSkybox();
		void updateTransforms();

        void drawWorldAxes() const;
        void drawSkybox() const;
        void submitMeshes() const;
        void submitLights() const;

    private:
        PerspectiveCamera m_cameraController;

        Entity m_skybox;
        Ref<UniformBuffer> m_pointLightsBuffer;
		Ref<UniformBuffer> m_directionalLightsBuffer;

		mutable entt::registry m_registry;
        friend class SceneUITools;
    };

} // namespace bbzl
