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

        void onEvent(Event& event);

    private:
        void drawHierarchyPanel();
        void drawComponentsPanel();
        void drawStatusPanel();

    private:
        Ref<Scene> m_scene;
        Entity m_selected;
    };
} // namespace butterfly
