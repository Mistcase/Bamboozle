#pragma once

#include "Bamboozle/Renderer/PipelineState.h"

namespace bbzl
{
    class VulkanDevice;

    class VulkanPipelineState : PipelineState
    {
    public:
        VulkanPipelineState(VulkanDevice& device);
        ~VulkanPipelineState();

        void term();

    private:
        bool createGraphicsPipeline();

    private:
        VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;
        VkPipeline m_pipeline = VK_NULL_HANDLE;

        VulkanDevice& m_device;
    };
    
} // namespace bbzl