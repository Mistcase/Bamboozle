#pragma once

#include <Butterfly.h>

namespace butterfly
{
    class Scene;

    class SceneUITools
    {
    public:
        void setScene(const Ref<Scene>& scene);
        void onImGuiRender();

    private:
        void drawHierarchyPanel();
        void drawComponentsPanel();

    private:
        Ref<Scene> m_scene;
        Entity m_selected;
    };
} // namespace butterfly
