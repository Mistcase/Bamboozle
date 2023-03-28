#pragma once

#include <Butterfly.h>

class Editor : public butterfly::Layer
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
	butterfly::Window& m_window;
	butterfly::Scene m_scene;
};
