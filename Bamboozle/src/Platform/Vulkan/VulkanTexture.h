#pragma once

#include "Bamboozle/Renderer/Texture.h"

namespace bbzl
{
    /*class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& path, Format format);
        OpenGLTexture2D(uint32_t width, uint32_t height);
        ~OpenGLTexture2D() override;

        void setData(const void* data, size_t size) override;

        void bind(uint32_t slot) const override;
        void unbind() const override;

        uint32_t getRendererId() const override;

		int getWidth() const override;
		int getHeight() const override;

		bool operator==(const Texture& other) override;

    private:
        uint32_t m_width, m_height, m_channels = 4;
        uint32_t m_rendererId;

		mutable uint32_t m_slot = 0;
    };*/

} // namespace bbzl
