#pragma once

namespace bbzl
{
    class VulkanDevice;
    class VulkanTexture2D;
    struct VulkanUniformBufferObject;

    class VulkanDescriptorSet
    {
    public:
        VulkanDescriptorSet(VulkanDevice& device);

        void newFrame();

        // TODO: REmove this, create layout object
        void setUBO(VulkanUniformBufferObject* ubo);
        void setTexture(VulkanTexture2D* texture);

 //   private:
        // TEMP
        VulkanUniformBufferObject* m_uniformBuffer = nullptr;
        VulkanTexture2D* m_texture = nullptr;

        VkDescriptorSetLayout m_layout = VK_NULL_HANDLE; // TODO: Remove from here
        VkDescriptorPool m_pool; // TODO: Remove from here
        VkDescriptorSet m_set = VK_NULL_HANDLE;

        VulkanDevice& m_device;
    };

} 