#pragma once

extern butterfly::Application* butterfly::CreateApplication();

int main(int argc, char** argv)
{
	butterfly::Log::Init();

	auto app = butterfly::CreateApplication();
	app->run();

	delete app;
}
