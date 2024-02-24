#pragma once

#include <glm/glm.hpp>

namespace bbzl
{
    struct VulkanUniformBufferObject
    {
        struct Data
        {
            glm::mat4 model;
            glm::mat4 view;
            glm::mat4 proj;  
        };

        void update();

        Data m_data;
        VkBuffer m_buffer;
        VkDeviceMemory m_bufferMem;
    };
}