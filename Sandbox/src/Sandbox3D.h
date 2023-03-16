#pragma once

#include <Butterfly.h>

class Sandbox3DLayer : public butterfly::Layer
{
public:
    Sandbox3DLayer();

    void onAttach() override;
    void onDetach() override;

    void onUpdate(float dt) override;
	void onImGuiRender() override;

	void onEvent(butterfly::Event& event) override;

private:
    bool onKeyEvent(const butterfly::KeyEvent& e);

private:
	std::unique_ptr<butterfly::PerspectiveCamera> m_camera;
	std::unique_ptr<butterfly::PerspectiveCameraController> m_cameraController;

	butterfly::Ref<butterfly::Object3D> m_teapot;

	glm::vec3 m_ambientColor;
	float m_ka;
	float m_kd;

	float m_phase = 0.0f;
};
