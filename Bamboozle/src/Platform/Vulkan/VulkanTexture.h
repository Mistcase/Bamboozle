#pragma once

#include "Bamboozle/Renderer/Texture.h"

namespace bbzl
{
    class VulkanTexture2D : public Texture2D
    {
        friend class VulkanDevice;

    public:
        ~VulkanTexture2D() override;

        void setData(const void* data, size_t size) override;

        void bind(uint32_t slot) const override;
        void unbind() const override;

        uint32_t getRendererId() const override;

		int getWidth() const override;
		int getHeight() const override;

        VkImageView getImageView() { return m_imageView; }
        VkSampler getSampler() { return m_sampler; }

		bool operator==(const Texture& other) override;

    private:
        VulkanTexture2D() = default;

    private:
        VkImage m_image = VK_NULL_HANDLE;
        VkImageView m_imageView = VK_NULL_HANDLE;
        VkSampler m_sampler = VK_NULL_HANDLE;

        uint32_t m_width, m_height, m_format;
        uint32_t m_rendererId;
	};

} // namespace bbzl
