#pragma once

#ifdef BUBBLE_PLATFORM_WINDOWS

extern bubble::Application* bubble::CreateApplication();

int main(int argc, char** argv)
{
	bubble::Log::Init();

	BUBBLE_CORE_WARN("Initialized Log!");
	BUBBLE_CLIENT_INFO("Hello!");

	auto app = bubble::CreateApplication();
	app->run();

	delete app;
}

#endif // BUBBLE_PLATFORM_WINDOWS
