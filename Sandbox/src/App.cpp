#include "Helpers.h"
#include "Sandbox2D.h"
#include "Sandbox3D.h"
#include "Editor.h"
#include <Bamboozle/EntryPoint.h>

class App : public bbzl::Application
{
public:
    App()
        : bbzl::Application("Sandbox", helpers::MakePath(""))
    {
        pushLayer(new Sandbox2DLayer());
    }

    ~App()
    {
    }
};

bbzl::Application* bbzl::CreateApplication()
{
    return new App();
}
