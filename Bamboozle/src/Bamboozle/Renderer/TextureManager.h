#pragma once

#include "Texture.h"

namespace bbzl
{
	class VidDeviceInterface;
	class VulkanTexture2D;

	class TextureManager
	{
	public:
        static void Init(VidDeviceInterface& device);

		Texture2D* createTexture(const std::filesystem::path& path, Texture2D::Format format);
		void destroyTexture(Texture2D* texture);

	private:
        TextureManager(VidDeviceInterface& device);

	private:
		VidDeviceInterface& m_device;
	};

    extern TextureManager* textureManager;
} // namespace bbzl
