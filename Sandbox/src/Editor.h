#pragma once

#include <Butterfly.h>

#include "SceneUITools.h"

namespace butterfly
{
    class EditorLayer : public Layer
    {
    public:
        EditorLayer();

        void onAttach() override;
        void onDetach() override;

        void onUpdate(float dt) override;
        void onImGuiRender() override;

        void onEvent(Event& event) override;

    private:
        void drawImGuiMenuBar();
        void drawImGuiViewport();

    private:
        Ref<Framebuffer> m_framebuffer;
        glm::vec2 m_oldViewportSize = { 0.0f, 0.0f };
        bool m_isViewportFocused = false;

    private:
        Window& m_window;
        Ref<Scene> m_scene;

        Entity m_wall;
        Entity m_directionalLight;

        Entity m_pointLight1;
        Entity m_pointLight2;

    private:
        SceneUITools m_UITools;
    };

} // namespace butterfly
