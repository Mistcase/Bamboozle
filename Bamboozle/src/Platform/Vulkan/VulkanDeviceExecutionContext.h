#pragma once

#include "Bamboozle/Renderer/DeviceExecutionContext.h"

namespace bbzl
{
    struct PipelineState;
}

namespace bbzl
{
    class VulkanDevice;

    class VulkanDeviceExecutionContext : public DeviceExecutionContextInterface
    {
    public:
        static constexpr size_t MAX_FRAMES_IN_FLIGHT = 2;

    public:
        VulkanDeviceExecutionContext(VulkanDevice& device);

        void bindPipeline(const PipelineState& pipeline);

        void testDraw(const PipelineState& pipeline, const Texture2D* texture) override;

        void beginFrame() override;
        void endFrame() override;

        void beginRenderPass() override;
        void endRenderPass() override;

    private:
        void createCommandBuffers();
        VkCommandBuffer getCurrentCommandBuffer() const;

    private:
        VulkanDevice& m_device;

        std::vector<VkCommandBuffer> m_commandBuffers;
        uint32_t m_currentFrameIndex = 0;
        bool m_isInFrame = false;

        VkBuffer m_testVertexBuffer;
        VkDeviceMemory m_testBufferMemory;
    };
}
