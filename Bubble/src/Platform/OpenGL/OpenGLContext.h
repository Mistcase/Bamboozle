#pragma once

#include "Bubble/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

struct GLFWwindow;

namespace bubble
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

} // namespace bubble