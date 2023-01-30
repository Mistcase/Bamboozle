#pragma once

#include "Butterfly/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace butterfly
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		void init() override;
		void swapBuffers() override;

	private:
		GLFWwindow* m_window;
	};

} // namespace butterfly
