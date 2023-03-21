#pragma once

#include <Butterfly.h>

class Sandbox3DLayer : public butterfly::Layer, public butterfly::Scene
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
};
