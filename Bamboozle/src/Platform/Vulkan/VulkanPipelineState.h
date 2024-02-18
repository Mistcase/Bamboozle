#pragma once

#include "Bamboozle/Renderer/PipelineState.h"

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
        
    private:
        bool createGraphicsPipeline();

    private:
        VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;
        VkPipeline m_pipeline = VK_NULL_HANDLE;

        VulkanDevice& m_device;
        bool m_isValid = false;
    };
    
} // namespace bbzl