#include "Bamboozle/bbzlpch.h"
#include "VulkanCommandBufferPool.h"

namespace bbzl
{
    void VulkanCommandBufferPool::beginFrame()
    {
        m_idxCurrent = m_idxCurrent + 1 % PoolSize;
    }

    void VulkanCommandBufferPool::endFrame()
    {
    }

    VulkanCommandBuffer VulkanCommandBufferPool::getCmdBuffer()
    {
        ASSERT_FAIL("Not implemented");
        return {};
        // return m_commandPools[m_idxCurrent];
    }
}
