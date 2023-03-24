#include "OpenGLContext.h"

#include "Butterfly/Log.h"
#include "Butterfly/butterflypch.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace butterfly
{
    OpenGLContext::OpenGLContext(GLFWwindow* window)
        : m_window(window)
    {
        BUTTERFLY_CORE_ASSERT(window != nullptr, "Window is null");
    }

    void OpenGLContext::init()
    {
        glfwMakeContextCurrent(m_window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        BUTTERFLY_CORE_ASSERT(status, "Failed to initialize Glad");

        BUTTERFLY_CORE_INFO("OpenGL renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
        BUTTERFLY_CORE_INFO("Version GLSL: {0}\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    }

    void OpenGLContext::swapBuffers()
    {
        glfwSwapBuffers(m_window);
    }
} // namespace butterfly
