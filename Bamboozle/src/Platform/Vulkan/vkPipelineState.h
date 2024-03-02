#pragma once

#include "Bamboozle/Renderer/PipelineState.h"

#include "VulkanDescriptorSet.h"

namespace bbzl
{
    class vkDevice;

    class vkPipelineState : public PipelineState
    {
    public:
        vkPipelineState(vkDevice& device);
        ~vkPipelineState() override;

        void validate() override;
        void bind() override;

        void term();

        VkPipeline getNativePipeline() const { return m_pipeline; }
        VkPipelineLayout getPipelineLayout() const { return m_pipelineLayout; }
        
    private:
        bool createGraphicsPipeline();

    private:
        VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;
        VkPipeline m_pipeline = VK_NULL_HANDLE;

        vkDevice& m_device;
        bool m_isValid = false;
    };
    
} // namespace bbzl