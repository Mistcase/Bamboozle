#include "Bamboozle/bbzlpch.h"
#include "VulkanContext.h"
#include "VulkanTexture.h"

#include "Bamboozle/Log.h"

namespace bbzl
{
    VulkanTexture2D::~VulkanTexture2D()
    {
		// TODO: Make device global object and rewrite it

        /*vkDestroyImageView(m_device, textureImageView, nullptr);

        vkDestroyImage(device, textureImage, nullptr);
        vkFreeMemory(device, textureImageMemory, nullptr);*/
    }

	void VulkanTexture2D::setData(const void* data, size_t size)
	{
        if (data == nullptr)
        {
            return;
        }

		ASSERT_FAIL("Not implemented");
	}

	void VulkanTexture2D::bind(uint32_t slot) const
	{
		ASSERT_FAIL("Not implemented");
	}

	void VulkanTexture2D::unbind() const
	{
		ASSERT_FAIL("Not implemented");
	}

	uint32_t VulkanTexture2D::getRendererId() const
	{
		return 0xbad; // TODO: Wtf is renderer id? What is purpose
	}

	int VulkanTexture2D::getWidth() const
	{
		return (int)m_width;
	}

	int VulkanTexture2D::getHeight() const
	{
		return (int)m_height;
	}

	bool VulkanTexture2D::operator==(const Texture& other)
	{
		ASSERT_FAIL("Not implemented");
		return false;
	}

} // namespace bbzl
