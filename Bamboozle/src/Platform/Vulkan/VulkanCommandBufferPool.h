#pragma once

#include "VulkanCommandBuffer.h"

namespace bbzl
{
    class VulkanCommandBufferPool
    {
    public:
        static constexpr size_t PoolSize = 2;

    public:
        void beginFrame();
        void endFrame();

        VulkanCommandBuffer getCmdBuffer();

    private:
        std::array<VkCommandPool, PoolSize> m_commandPools;
        size_t m_idxCurrent = 0;
    };

}
