#pragma once

#include "Butterfly/Core.h"
#include "Butterfly/Renderer/PerspectiveCamera.h"
#include "Butterfly/Scene/Entity.h"

#include <vector>

namespace butterfly
{
    class DirectionalLight;
    class UniformBuffer;

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
		void updateTransforms();

        void drawWorldAxes() const;
        void submitMeshes() const;
        void submitLights() const;

    private:
        PerspectiveCamera m_cameraController;

    private:
        Ref<UniformBuffer> m_pointLightsBuffer;
		Ref<UniformBuffer> m_directionalLightsBuffer;

	private:
		mutable entt::registry m_registry;
        friend class SceneUITools;
    };

} // namespace butterfly
