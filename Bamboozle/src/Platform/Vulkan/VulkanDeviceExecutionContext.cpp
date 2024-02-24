#include "Bamboozle/bbzlpch.h"
#include "VulkanContext.h"
#include "VulkanDeviceExecutionContext.h"

#include "VulkanUniformBuffer.h"

#include "TestVertex.h"

#include "VulkanDevice.h"
#include "VulkanPipelineState.h"
#include "Bamboozle/Log.h"

namespace bbzl
{
    std::vector<Vertex> quads = {
        { { -0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0, 0 } },
        { { 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1, 0 } },
        { { -0.5f, 0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0, 1 } },

        { { 0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1, 0 } },
        { { 0.5f, 0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1, 1 } },
        { { -0.5f, 0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0, 1 } },
    };

    VulkanUniformBufferObject uniformBuffer;

    VulkanDeviceExecutionContext::VulkanDeviceExecutionContext(VulkanDevice& device)
        : m_device(device)
    {
        createCommandBuffers();

        // Test vertex buffer
        auto vertexCount = (uint32_t)quads.size();
        VkDeviceSize bufferSize = sizeof(quads[0]) * vertexCount;
        device.createBuffer(bufferSize,
                            VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, // Host - CPU, Device - GPU, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT - Access from cpu side, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT - Mapping CPU mem <-> GPU mem
                            m_testVertexBuffer,
                            m_testBufferMemory);

        void* data;
        vkMapMemory(device.getNativeDevice(), m_testBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, quads.data(), (size_t)bufferSize);
        vkUnmapMemory(device.getNativeDevice(), m_testBufferMemory);

        // Create ubo
        unsigned char zerodata[sizeof(VulkanUniformBufferObject::Data)]{};
        device.createBuffer(sizeof(VulkanUniformBufferObject::Data),
                            VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, // Host - CPU, Device - GPU, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT - Access from cpu side, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT - Mapping CPU mem <-> GPU mem
                            uniformBuffer.m_buffer,
                            uniformBuffer.m_bufferMem);

        {
            void* data;
            vkMapMemory(device.getNativeDevice(), uniformBuffer.m_bufferMem, 0, sizeof(VulkanUniformBufferObject::Data), 0, &data);
            memcpy(data, zerodata, (size_t)sizeof(VulkanUniformBufferObject::Data));
            vkUnmapMemory(device.getNativeDevice(), uniformBuffer.m_bufferMem);
        }
    }

    void VulkanDeviceExecutionContext::bindPipeline(const PipelineState& pipeline)
    {
        const auto currentCommandBuffer = getCurrentCommandBuffer();
        const auto& vkPipeline = static_cast<const VulkanPipelineState&>(pipeline);

        vkCmdBindPipeline(currentCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vkPipeline.getNativePipeline());
    }

    void VulkanDeviceExecutionContext::testDraw(const PipelineState& pipeline, const Texture2D* _texture)
    {
        VulkanTexture2D* texture = (VulkanTexture2D*)_texture;

        VulkanPipelineState& vkPipeline = const_cast<VulkanPipelineState&>((const VulkanPipelineState&)(pipeline));
        auto currentCB = getCurrentCommandBuffer();

        auto& renderPassLayout = const_cast<VulkanPipelineState&>(vkPipeline).getRenderPassLayout();
        renderPassLayout[0].setTexture(texture);
        renderPassLayout[0].setUBO(&uniformBuffer);
        renderPassLayout[0].newFrame(); // Update descriptor set

        vkCmdBindDescriptorSets(currentCB, VK_PIPELINE_BIND_POINT_GRAPHICS, vkPipeline.getPipelineLayout(), 0, 1, &renderPassLayout[0].m_set, 0, nullptr);

        VkBuffer buffers[] = { m_testVertexBuffer };
        VkDeviceSize offsets[] = { 0, offsetof(Vertex, color), offsetof(Vertex, texCoords) }; // Offsets in vertex, bind layout

        vkCmdBindVertexBuffers(currentCB, 0, 1, buffers, offsets);
        vkCmdDraw(currentCB, 6, 1, 0, 0);
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
