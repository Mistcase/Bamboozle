#pragma once

#include "Bubble/Renderer/Texture.h"

namespace bubble
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& path);
        OpenGLTexture2D(uint32_t width, uint32_t height);
        ~OpenGLTexture2D() override;

        void setData(const void* data, size_t size) override;

        void bind() override;
        void unbind() override;

    private:
        uint32_t m_width, m_height, m_channels;
        uint32_t m_rendererId;
    };

} // namespace bubble
