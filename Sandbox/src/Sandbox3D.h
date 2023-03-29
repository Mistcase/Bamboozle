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

    butterfly::Ref<butterfly::Texture2D> m_texture;
    butterfly::Object3D* m_teapot;
    butterfly::Object3D* m_skybox;
    butterfly::Object3D* m_barrel;

private:
	bool m_oldCursorVisible = true;
	butterfly::Window& m_window;
};
