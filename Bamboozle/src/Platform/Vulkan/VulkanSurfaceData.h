#pragma once

#include <vulkan/vulkan_core.h>

namespace bbzl
{
    struct VulkanSurfaceData
    {
        VkInstance instance;
        VkSurfaceKHR* surface;
    };

} // namespace bbzl
