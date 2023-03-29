#pragma once

#include <Butterfly.h>

class Sandbox2DLayer : public butterfly::Layer
{
public:
    Sandbox2DLayer();

    void onAttach() override;
    void onDetach() override;

    void onUpdate(float dt) override;
    void onImGuiRender() override;

    void onEvent(butterfly::Event& event) override;

private:
    bool onKeyEvent(const butterfly::KeyEvent& e);

private:
    std::unique_ptr<butterfly::PerspectiveCamera> m_pcamera;

    std::unique_ptr<butterfly::Camera> m_camera;
    std::unique_ptr<butterfly::CameraController> m_cameraController;
    butterfly::Ref<butterfly::Texture2D> m_texture;
    butterfly::Ref<butterfly::Texture2D> m_texture2;
    butterfly::Ref<butterfly::Framebuffer> m_framebuffer;
};
