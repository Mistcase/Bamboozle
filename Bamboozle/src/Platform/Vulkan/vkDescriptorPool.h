#pragma once

#include "VulkanContext.h"

namespace bbzl
{
    class vkDescriptorPool final
    {
    public:
        vkDescriptorPool();
        ~vkDescriptorPool();

        VkDescriptorSet allocateSet(const VkDescriptorSetLayout& layout, uint32_t count = 1);

    private:
        VkDescriptorPool m_pool;
    };
}
