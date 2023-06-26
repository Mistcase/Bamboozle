#include "Helpers.h"
#include "Sandbox2D.h"
#include "Sandbox3D.h"
#include "Editor.h"
#include <Bamboozle/EntryPoint.h>

class Sandbox : public bbzl::Application
{
public:
    Sandbox()
        : bbzl::Application("Sandbox", helpers::MakePath(""))
    {
        pushLayer(new bbzl::EditorLayer());
    }

    ~Sandbox()
    {
    }
};

bbzl::Application* bbzl::CreateApplication()
{
    return new Sandbox();
}
