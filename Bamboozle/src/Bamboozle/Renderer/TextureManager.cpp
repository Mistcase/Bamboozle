#include "Bamboozle/bbzlpch.h"
#include "TextureManager.h"

#include "Bamboozle/Log.h"
#include "Bamboozle/Renderer/Renderer.h"
#include "Platform/Vulkan/VulkanDevice.h"
#include "Platform/Vulkan/VulkanTexture.h"
#include "Platform/Vulkan/VulkanContext.h"

#include "stb_image.h"

namespace bbzl
{
    TextureManager* textureManager = nullptr;

	TextureManager::TextureManager(VidDeviceInterface& device)
		: m_device(device)
	{
	}

    void TextureManager::Init(VidDeviceInterface& device)
    {
		// TODO: deallocate it
        textureManager = new TextureManager(device);
    }

	Texture2D* TextureManager::createTexture(const std::filesystem::path& path, Texture2D::Format format)
	{
		BBZL_CORE_INFO("Creating {} texture {}", Texture2D::FormatNames[format], path);

		int width, height, channels;
        auto* data = stbi_load(path.generic_string().c_str(), &width, &height, &channels, STBI_rgb_alpha);
        ASSERT(data != nullptr);
        ASSERT((channels == 3 && format == Texture2D::Format::R8G8B8) ||
               (channels == 4 && format == Texture2D::Format::R8G8B8A8) ||
               (channels == 1 && format == Texture2D::Format::R8));

		Texture2D* texture = nullptr;
		const auto apiType = Renderer::GetAPI();
		if (apiType == RenderAPI::API_TYPE::Vulkan)
		{
			texture = static_cast<VulkanDevice&>(m_device).createTexture(width, height, format, data);
		}
		else
		{
			ASSERT_FAIL("API is not supported!");
		}

		stbi_image_free(data);
		return texture;
	}

	void TextureManager::destroyTexture(Texture2D* texture)
	{
		delete texture;
	}

} // namespace bbzl
