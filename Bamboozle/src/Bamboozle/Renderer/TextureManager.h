#pragma once

#include "Texture.h"

namespace bbzl
{
	class RenderDevice;
	class VulkanTexture2D;

	class TextureManager
	{
	public:
        static void Init(RenderDevice& device);

		Texture2D* createTexture(const std::filesystem::path& path, Texture2D::Format format);
		void destroyTexture(Texture2D* texture);

	private:
        TextureManager(RenderDevice& device);

	private:
		RenderDevice& m_device;
	};

    extern TextureManager* textureManager;
} // namespace bbzl
