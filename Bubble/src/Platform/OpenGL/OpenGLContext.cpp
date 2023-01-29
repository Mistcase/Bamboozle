#include "Bubble/bubblepch.h"
#include "OpenGLContext.h"
#include "Bubble/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace bubble
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_window(window)
	{
		BUBBLE_CORE_ASSERT(window != nullptr, "Window is null");
	}

	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(m_window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BUBBLE_CORE_ASSERT(status, "Failed to initialize Glad");

        BUBBLE_CORE_INFO("OpenGL renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		BUBBLE_CORE_INFO("Version GLSL: {0}\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}
