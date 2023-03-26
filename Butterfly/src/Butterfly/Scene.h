#pragma once

#include "Butterfly/Core.h"
#include "Butterfly/DirectionalLight.h"
#include "Butterfly/PerspectiveCameraController.h"
#include "Butterfly/Renderer/PerspectiveCamera.h"
#include "Butterfly/PointLight.h"
#include <vector>

namespace butterfly
{
    class DirectionalLight;
    class Object3D;
    class UniformBuffer;

    class Scene
    {
    public:
        using PointLights = std::vector<PointLight>;
		using DirectionalLights = std::vector<DirectionalLight>;
        using Objects = std::vector<Ref<Object3D>>;

    public:
        Scene();

        void update(float dt);
        void render() const;

        const PointLights& getPointLights() const;
		const DirectionalLights& getDirectionalLights() const;

        const Objects getObjects() const;

    protected:
        void drawWorldAxes() const;
        void submitLights() const;

    protected:
        Ref<PerspectiveCamera> m_camera;
        Ref<PerspectiveCameraController> m_cameraController;

        PointLights m_pointLights;
		DirectionalLights m_directionalLights;
        Objects m_objects;

    protected:
        Ref<UniformBuffer> m_pointLightsBuffer;
		Ref<UniformBuffer> m_directionalLightsBuffer;
    };

} // namespace butterfly
