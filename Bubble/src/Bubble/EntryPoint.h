#pragma once

extern bubble::Application* bubble::CreateApplication();

int main(int argc, char** argv)
{
	bubble::Log::Init();

	auto app = bubble::CreateApplication();
	app->run();

	delete app;
}
