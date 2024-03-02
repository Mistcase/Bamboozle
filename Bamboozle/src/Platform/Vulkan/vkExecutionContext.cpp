#include "Bamboozle/bbzlpch.h"
#include "VulkanContext.h"
#include "vkExecutionContext.h"

#include "VulkanUniformBuffer.h"

#include "vkDescriptorPool.h"

#include "vkDevice.h"
#include "vkPipelineState.h"
#include "Bamboozle/Log.h"
#include "Bamboozle/Renderer/DescriptorSetLayout.h"
#include "Bamboozle/Renderer/DeviceExecutionContextFwd.h"

namespace bbzl
{
    vkDeviceExecutionContext::vkDeviceExecutionContext(vkDevice& device)
        : m_device(device)
    {
        createCommandBuffers();
        createCommonDescriptorSets();
    }

    void vkDeviceExecutionContext::setDescriptorSet(VkDescriptorSet set)
    {
        m_frameDescriptorSets[DS_ID_PASS_SPECIFIC] = set;
    }

    void vkDeviceExecutionContext::setPSO(const PipelineState& pipeline)
    {
        m_pso = (vkPipelineState*)(&pipeline);
        vkCmdBindPipeline(getCmdBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, m_pso->getNativePipeline());
    }

    void vkDeviceExecutionContext::draw(size_t vertexCount, size_t instanceCount)
    {
        // beginRenderPass();

        // Update constant buffers
        ensureDescriptorSets();

        vkCmdDraw(getCmdBuffer(), vertexCount, instanceCount, 0, 0);

        // endRenderPass();
    }

    void vkDeviceExecutionContext::beginFrame()
    {
        // Clear command buffer
        auto commandBuffer = getCmdBuffer();
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        VK_CALL(vkBeginCommandBuffer(commandBuffer, &beginInfo));
        m_isInFrame = true;
    }

    void vkDeviceExecutionContext::endFrame()
    {
        const auto commandBuffer = getCmdBuffer();
        const auto isCmdBufEnd = vkEndCommandBuffer(commandBuffer);
        ASSERT(isCmdBufEnd == VK_SUCCESS);

        auto result = m_device.getSwapChain().submitCommandBuffers(&commandBuffer);
        ASSERT(result == VK_SUCCESS);

        m_frameIdx = (m_frameIdx + 1) % MAX_FRAMES_IN_FLIGHT;
        m_isInFrame = false;
    }

    void vkDeviceExecutionContext::beginRenderPass()
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

        auto commandBuffer = getCmdBuffer();
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

    void vkDeviceExecutionContext::endRenderPass()
    {
        vkCmdEndRenderPass(getCmdBuffer());
        m_frameDescriptorSets[DS_ID_PASS_SPECIFIC] = VK_NULL_HANDLE;
    }

    void vkDeviceExecutionContext::ensureDescriptorSets() const
    {
        ASSERT(m_frameDescriptorSets[DS_ID_COMMON] != VK_NULL_HANDLE, "Common set must created with context");

        const auto vkPSOLayout = m_pso->getPipelineLayout();
        const auto cmdBuffer = getCmdBuffer();
        const auto count = m_frameDescriptorSets[DS_ID_PASS_SPECIFIC] != VK_NULL_HANDLE ? 2 : 1;
        const auto* psets = m_frameDescriptorSets.data();

        vkCmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vkPSOLayout, 0, count, psets, 0, nullptr);
    }

    void vkDeviceExecutionContext::createCommandBuffers()
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

    void vkDeviceExecutionContext::createCommonDescriptorSets()
    {
        // DS manager must be already initialized here
        const auto& layout = m_device.getDescriptorSets().getPSOLayout(ShaderPassType::PASS_COMMON);
        m_frameDescriptorSets[DS_ID_COMMON] = vkDescriptorPool().allocateSet(layout.layout);
    }

    VkCommandBuffer vkDeviceExecutionContext::getCmdBuffer() const
    {
        return m_commandBuffers[m_frameIdx];
    }

    vkDeviceExecutionContext* getVkDeviceContext()
    {
        ASSERT(g_RenderContext);
        return static_cast<vkDeviceExecutionContext*>(g_RenderContext);
    }
}
