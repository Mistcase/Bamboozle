#include "VulkanContext.h"

#include "Bamboozle/Assert.h"
#include "Bamboozle/Log.h"
#include "Bamboozle/bbzl.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace bbzl
{
    VulkanContext::VulkanContext()
    {
        // ASSERT(window != nullptr, "Window is null");
    }

    void VulkanContext::init()
    {
    /*    glfwMakeContextCurrent(m_window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        ASSERT(status, "Failed to initialize Glad");

        BBZL_CORE_INFO("OpenGL renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
        BBZL_CORE_INFO("Version GLSL: {0}\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    */}

    void VulkanContext::swapBuffers()
    {
        glfwSwapBuffers(m_window);
    }
} // namespace bbzl
