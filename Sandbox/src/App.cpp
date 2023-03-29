#include "Helpers.h"
#include "Sandbox2D.h"
#include "Sandbox3D.h"
#include "Editor.h"
#include <Butterfly/EntryPoint.h>

class Sandbox : public butterfly::Application
{
public:
    Sandbox()
        : butterfly::Application("Sandbox", helpers::MakePath(""))
    {
        pushLayer(new butterfly::EditorLayer());
    }

    ~Sandbox()
    {
    }
};

butterfly::Application* butterfly::CreateApplication()
{
    return new Sandbox();
}
