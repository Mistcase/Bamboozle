#pragma once

#include "Bamboozle/Renderer/DeviceExecutionContext.h"

#include "vkPipelineState.h"

namespace bbzl
{
    class vkDevice;
    class vkDeviceExecutionContext : public DeviceExecutionContext
    {
        enum DescriptorSetId
        {
            DS_ID_COMMON,
            DS_ID_PASS_SPECIFIC,

            DS_ID_COUNT
        };

    public:
        static constexpr size_t MAX_FRAMES_IN_FLIGHT = 2;
        static constexpr size_t DESCRIPTOR_SETS_PER_FRAME = DS_ID_COUNT;

        using vkCommandBuffers = std::vector<VkCommandBuffer>;
        using vkFrameDescriptorSets = std::array<VkDescriptorSet, DESCRIPTOR_SETS_PER_FRAME>;
        using vkDescriptorSetList = std::vector<VkDescriptorSet>;

    public:
        vkDeviceExecutionContext(vkDevice& device);

        void setDescriptorSet(VkDescriptorSet set);
        void setPSO(const PipelineState& pipeline) override;

        void draw(size_t vertexCount, size_t instanceCount) override;

        void beginFrame() override;
        void endFrame() override;

        void beginRenderPass() override;
        void endRenderPass() override;

        VkCommandBuffer getCmdBuffer() const;

    private:
        void createCommandBuffers();
        void createCommonDescriptorSets();

        // Flush constant buffer
        void ensureDescriptorSets() const;

    private:
        vkDevice& m_device;
        vkCommandBuffers m_commandBuffers;

        vkFrameDescriptorSets m_frameDescriptorSets{};
        vkPipelineState* m_pso = nullptr;

        uint32_t m_frameIdx = 0;
        bool m_isInFrame = false;
    };

    vkDeviceExecutionContext* getVkDeviceContext();
}
