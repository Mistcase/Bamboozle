#include <Bubble.h>

class ExampleLayer : public bubble::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void onUpdate() override
	{
		BUBBLE_CLIENT_INFO("ExampleLayer::Update");
	}

	void onEvent(bubble::Event& event) override
	{
		BUBBLE_CLIENT_TRACE("{0}", event);
	}

};

class Sandbox : public bubble::Application
{
public:
	Sandbox()
	{
		pushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

bubble::Application* bubble::CreateApplication()
{
	return new Sandbox();
}