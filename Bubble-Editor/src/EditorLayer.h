#pragma once

#include <Bubble.h>

class EditorLayer : public bubble::Layer
{
public:
    EditorLayer();

    void onAttach() override;
    void onDetach() override;

    void onUpdate(float dt) override;
	void onImGuiRender() override;

	void onEvent(bubble::Event& event) override;

private:
    bool onKeyEvent(const bubble::KeyEvent& e);

private:
    std::unique_ptr<bubble::Camera> m_camera;
    std::unique_ptr<bubble::CameraController> m_cameraController;
    bubble::Ref<bubble::Texture2D> m_texture;
    bubble::Ref<bubble::Texture2D> m_texture2;
    bubble::Ref<bubble::Framebuffer> m_framebuffer;

    glm::vec2 m_viewportSize;
};
