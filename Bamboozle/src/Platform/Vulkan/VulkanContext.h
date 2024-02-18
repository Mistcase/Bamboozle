#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Bamboozle/Renderer/GraphicsContext.h"

namespace bbzl
{
    class VulkanContext : public GraphicsContext
    {
    public:
        VulkanContext();

        void init() override;
        void swapBuffers() override;

    private:
        GLFWwindow* m_window;
    };

} // namespace bbzl
