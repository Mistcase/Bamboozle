#include "Sandbox2D.h"
#include "Sandbox3D.h"

#include "Helpers.h"

#include <Butterfly/EntryPoint.h>

class Sandbox : public butterfly::Application
{
public:
	Sandbox()
        : butterfly::Application("Sandbox", helpers::MakePath(""))
	{
        pushLayer(new Sandbox3DLayer());
	}

	~Sandbox()
	{
	}
};

butterfly::Application* butterfly::CreateApplication()
{
	return new Sandbox();
}
