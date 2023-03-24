#pragma once

#include "Butterfly/Core.h"
#include "Butterfly/PerspectiveCameraController.h"
#include "Butterfly/Renderer/PerspectiveCamera.h"
#include "PointLight.h"
#include <vector>

namespace butterfly
{
    class DirectionalLight;
    class Object3D;
    class UniformBuffer;

    class Scene
    {
    public:
        using Lights = std::vector<PointLight>;
        using Objects = std::vector<Ref<Object3D>>;

    public:
        Scene();

        void update(float dt);
        void render() const;

        virtual void renderImGui();

        const Lights& getLights() const;
        const Objects getObjects() const;

    protected:
        void drawWorldAxes() const;
        void submitLights() const;

    protected:
        Ref<PerspectiveCamera> m_camera;
        Ref<PerspectiveCameraController> m_cameraController;

        Lights m_lights;
        Objects m_objects;

    protected:
        Ref<UniformBuffer> m_pointLightsBuffer;
    };

} // namespace butterfly
