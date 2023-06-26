#pragma once

#include <Bamboozle/bbzl.h>

class Sandbox3DLayer : public bbzl::Layer
{
public:
    Sandbox3DLayer();

    void onAttach() override;
    void onDetach() override;

    void onUpdate(float dt) override;
    void onImGuiRender() override;

    void onEvent(bbzl::Event& event) override;

private:
    bool onKeyEvent(const bbzl::KeyEvent& e);

    bbzl::Ref<bbzl::Texture2D> m_texture;
    bbzl::Object3D* m_teapot;
    bbzl::Object3D* m_skybox;
    bbzl::Object3D* m_barrel;

private:
	bool m_oldCursorVisible = true;
	bbzl::Window& m_window;
};
