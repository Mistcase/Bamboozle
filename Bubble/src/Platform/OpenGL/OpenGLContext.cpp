#include "bubblepch.h"
#include "OpenGLContext.h"
#include "Bubble/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

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

        BUBBLE_CORE_INFO("OpenGL renderer: {0}", glGetString(GL_RENDERER));
	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}
