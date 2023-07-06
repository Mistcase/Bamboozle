#pragma once

#include <Bamboozle/bbzl.h>

class Sandbox2DLayer : public bbzl::Layer
{
public:
    Sandbox2DLayer();

    void onAttach() override;
    void onDetach() override;

    void onUpdate(float dt) override;
	void onRender() override;

    void onImGuiRender() override;

    void onEvent(bbzl::Event& event) override;

private:
    bool onKeyEvent(const bbzl::KeyEvent& e);

private:
    std::unique_ptr<bbzl::OrthographicCamera> m_camera;
};
