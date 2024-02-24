#pragma once

#include "Bamboozle/Renderer/PipelineState.h"

#include "VulkanDescriptorSet.h"

namespace bbzl
{
    class VulkanDevice;

    class VulkanPipelineState : public PipelineState
    {
    public:
        VulkanPipelineState(VulkanDevice& device);
        ~VulkanPipelineState() override;

        void validate() override;
        void bind() override;

        void term();

        VkPipeline getNativePipeline() const { return m_pipeline; }

        // TODO: Move it to render pass class later
        using RenderPassLayout = std::vector<VulkanDescriptorSet>;
        RenderPassLayout& getRenderPassLayout() { return m_renderPassLayout; }
        VkPipelineLayout getPipelineLayout() { return m_pipelineLayout; }
        
    private:
        bool createGraphicsPipeline();

        [[deprecated]] void createRenderPassLayout();

    private:
        VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;
        VkPipeline m_pipeline = VK_NULL_HANDLE;

        RenderPassLayout m_renderPassLayout;

        VulkanDevice& m_device;
        bool m_isValid = false;
    };
    
} // namespace bbzl