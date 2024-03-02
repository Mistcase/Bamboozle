#include "Bamboozle/bbzlpch.h"
#include "VulkanContext.h"
#include "vkDescriptorPool.h"

#include "vkDevice.h"

extern bbzl::RenderDevice* RenderDevice;

namespace bbzl
{
    vkDescriptorPool::vkDescriptorPool()
    {
        static constexpr uint32_t MAX_SETS_COUNT = 2; 
        static constexpr uint32_t MAX_UBO_COUNT = 4;
        static constexpr uint32_t MAX_SAMPLERS_COUNT = 5;

        const std::array<VkDescriptorPoolSize, 2> poolSizes = {
            VkDescriptorPoolSize{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, MAX_UBO_COUNT },
            VkDescriptorPoolSize{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, MAX_SAMPLERS_COUNT }
        };

        VkDescriptorPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
        poolInfo.pPoolSizes = poolSizes.data();
        poolInfo.maxSets = MAX_SETS_COUNT;

        VK_CALL(vkCreateDescriptorPool(getVkDeviceNative(), &poolInfo, nullptr, &m_pool));
    }

    vkDescriptorPool::~vkDescriptorPool()
    {
        vkDestroyDescriptorPool(getVkDeviceNative(), m_pool, nullptr);
    }

    VkDescriptorSet vkDescriptorPool::allocateSet(const VkDescriptorSetLayout& layout, uint32_t count)
    {
        ASSERT(count == 1);

        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.pNext = nullptr;
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = m_pool;
        allocInfo.descriptorSetCount = count;
        allocInfo.pSetLayouts = &layout;

        VkDescriptorSet set;
        VK_CALL(vkAllocateDescriptorSets(getVkDeviceNative(), &allocInfo, &set));

        return set;
    }
}
