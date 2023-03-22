#pragma once

#include "Butterfly/Core.h"
#include "Butterfly/Renderer/PerspectiveCamera.h"
#include "Butterfly/PerspectiveCameraController.h"
#include "DirectionalLight.h"

#include <vector>

namespace butterfly
{
    class DirectionalLight;
    class Object3D;

    class Scene
    {
    public:
        using Lights = std::vector<DirectionalLight>;
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

        void test(float dt);

    protected:
        Ref<PerspectiveCamera> m_camera;
        Ref<PerspectiveCameraController> m_cameraController;

        Lights m_lights;
        Objects m_objects;
    };

} // namespace butterfly
