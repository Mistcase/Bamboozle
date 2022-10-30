#include <Bubble.h>

class Sandbox : public bubble::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

bubble::Application* bubble::CreateApplication()
{
	return new Sandbox();
}