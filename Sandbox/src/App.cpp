#include "Sandbox2D.h"

#include "Helpers.h"

#include <Butterfly/EntryPoint.h>

class Sandbox : public butterfly::Application
{
public:
	Sandbox()
        : butterfly::Application("Sandbox", helpers::MakePath(""))
	{
        pushLayer(new Sandbox2DLayer());
	}

	~Sandbox()
	{
	}
};

butterfly::Application* butterfly::CreateApplication()
{
	return new Sandbox();
}
