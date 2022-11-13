#include "bubblepch.h"
#include "OpenGLTexture.h"

#include "Bubble/Log.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace bubble
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
    {
        glGenTextures(1, &m_rendererId);
        glBindTexture(GL_TEXTURE_2D, m_rendererId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_set_flip_vertically_on_load(1);

        int width, height, channels;
        auto data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        BUBBLE_CORE_ASSERT(data != nullptr, "Failed to load image");

        const auto format = channels == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_rendererId);
    }

    void OpenGLTexture2D::bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_rendererId);
    }

    void OpenGLTexture2D::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

} // namespace bubble
