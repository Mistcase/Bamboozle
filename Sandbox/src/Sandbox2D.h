#pragma once

#include <Bubble.h>

class Sandbox2DLayer : public bubble::Layer
{
public:
    Sandbox2DLayer();

    void onAttach() override;
    void onDetach() override;

    void onUpdate(float dt) override;
	void onImGuiRender() override;

	void onEvent(bubble::Event& event) override;

private:
    std::unique_ptr<bubble::Camera> m_camera;
    std::unique_ptr<bubble::CameraController> m_cameraController;
    bubble::Ref<bubble::Texture2D> m_texture;
};
