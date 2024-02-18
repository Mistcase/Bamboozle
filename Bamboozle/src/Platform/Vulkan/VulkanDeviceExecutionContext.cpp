#include "Bamboozle/bbzlpch.h"
#include "VulkanContext.h"
#include "VulkanDeviceExecutionContext.h"

#include "VulkanDevice.h"
#include "Bamboozle/Log.h"

namespace bbzl
{
    VulkanDeviceExecutionContext::VulkanDeviceExecutionContext(VulkanDevice& device)
        : m_device(device)
    {
        createCommandBuffers();
    }

    void VulkanDeviceExecutionContext::beginFrame()
    {
        // Clear command buffer
        auto commandBuffer = getCurrentCommandBuffer();
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        // TODO: return false??
        [[maybe_unused]] const auto result = vkBeginCommandBuffer(commandBuffer, &beginInfo);
        

        m_isInFrame = true;
    }

    void VulkanDeviceExecutionContext::endFrame()
    {
        const auto commandBuffer = getCurrentCommandBuffer();
        const auto isCmdBufEnd = vkEndCommandBuffer(commandBuffer);
        ASSERT(isCmdBufEnd == VK_SUCCESS);

        auto result = m_device.getSwapChain().submitCommandBuffers(&commandBuffer);
        ASSERT(result == VK_SUCCESS);

        m_currentFrameIndex = (m_currentFrameIndex + 1) % MAX_FRAMES_IN_FLIGHT;
        m_isInFrame = false;
    }

    void VulkanDeviceExecutionContext::beginRenderPass()
    {
        auto& swapChain = m_device.getSwapChain();
        swapChain.swapBuffers();

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = swapChain.getRenderPass();
        renderPassInfo.framebuffer = swapChain.getCurrentFrameBuffer();

        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = swapChain.getSwapChainExtent();

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = { 1.0f, 0.1f, 0.1f, 1.0f };
        clearValues[1].depthStencil = { 1.0f, 0 };

        renderPassInfo.clearValueCount = (uint32_t)clearValues.size();
        renderPassInfo.pClearValues = clearValues.data();

        auto commandBuffer = getCurrentCommandBuffer();
        vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = static_cast<float>(swapChain.getSwapChainExtent().width);
        viewport.height = static_cast<float>(swapChain.getSwapChainExtent().height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        VkRect2D scissor{ { 0, 0 }, swapChain.getSwapChainExtent() };
        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
    }

    void VulkanDeviceExecutionContext::endRenderPass()
    {
        vkCmdEndRenderPass(getCurrentCommandBuffer());
    }

    void VulkanDeviceExecutionContext::createCommandBuffers()
    {
        m_commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

        VkCommandBufferAllocateInfo info{};
        info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        info.commandPool = m_device.getCommandPool(); // Commands allocated from this pool
        info.commandBufferCount = (uint32_t)m_commandBuffers.size();

        if (vkAllocateCommandBuffers(m_device.getNativeDevice(), &info, m_commandBuffers.data()) != VK_SUCCESS)
        {
            ASSERT_FAIL_NO_MSG();
        }
    }

    VkCommandBuffer VulkanDeviceExecutionContext::getCurrentCommandBuffer() const
    {
        return m_commandBuffers[m_currentFrameIndex];
    }

}
