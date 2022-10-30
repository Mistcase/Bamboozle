#pragma once

#include "Core.h"

namespace bubble
{
	class BUBBLE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	// Have to be defined by client
	Application* CreateApplication();

} // namespace bubble
