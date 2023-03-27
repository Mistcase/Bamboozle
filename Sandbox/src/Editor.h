#pragma once

#include <Butterfly.h>

class Editor : public butterfly::Layer, public butterfly::Scene
{
public:
	Editor();

	void onAttach() override;
    void onDetach() override;

    void onUpdate(float dt) override;
    void onImGuiRender() override;

	void onEvent(butterfly::Event& event) override;

private:
	butterfly::Ref<butterfly::Framebuffer> m_framebuffer;
	glm::vec2 m_oldViewportSize = { 0.0f, 0.0f };

	bool m_isViewportFocused = false;

private:
	butterfly::Ref<butterfly::Texture2D> m_texture;
    butterfly::Object3D* m_teapot;
    butterfly::Object3D* m_skybox;
    butterfly::Object3D* m_barrel;

private:
	butterfly::Window& m_window;
};
