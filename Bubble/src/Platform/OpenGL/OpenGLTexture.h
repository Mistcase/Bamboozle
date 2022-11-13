#pragma once

#include "Bubble/Renderer/Texture.h"

namespace bubble
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D() override;

        void bind() override;
        void unbind() override;

    private:
        uint32_t m_rendererId;
    };

} // namespace bubble
