#pragma once

#include <vulkan/vulkan_core.h>

namespace bbzl
{
    class VulkanCommandBuffer
    {
    public:
        // Vulkan command buffer states mapping.
        enum class State
        {
            Initial,
            Recording,
            Executable,
            Pending,
            Invalid,

            Count
        };

        VulkanCommandBuffer()
            : m_commandBuffer(VK_NULL_HANDLE)
            , m_state(State::Initial)
        {
        }

        VkCommandBuffer m_commandBuffer;
        State m_state;
    };
    
} // namespace bbzl