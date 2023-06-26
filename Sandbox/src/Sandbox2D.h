#pragma once

#include <Bamboozle/bbzl.h>

class Sandbox2DLayer : public bbzl::Layer
{
public:
    Sandbox2DLayer();

    void onAttach() override;
    void onDetach() override;

    void onUpdate(float dt) override;
    void onImGuiRender() override;

    void onEvent(bbzl::Event& event) override;

private:
    bool onKeyEvent(const bbzl::KeyEvent& e);

private:
    std::unique_ptr<bbzl::PerspectiveCamera> m_pcamera;

    std::unique_ptr<bbzl::Camera> m_camera;
    std::unique_ptr<bbzl::CameraController> m_cameraController;
    bbzl::Ref<bbzl::Texture2D> m_texture;
    bbzl::Ref<bbzl::Texture2D> m_texture2;
    bbzl::Ref<bbzl::Framebuffer> m_framebuffer;
};
