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
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_rendererId);

        glTextureParameteri(m_rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

        stbi_set_flip_vertically_on_load(1);

        int width, height, channels;
        auto data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        BUBBLE_CORE_ASSERT(data != nullptr, "Failed to load image");

        m_width = static_cast<uint32_t>(width);
        m_height = static_cast<uint32_t>(height);
        m_channels = static_cast<uint32_t>(channels);

        const auto format = m_channels == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : m_width(width)
        , m_height(height)
    {
        glGenTextures(1, &m_rendererId);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_rendererId);

        const auto format = m_channels == 3 ? GL_RGB8 : GL_RGBA8;
        glTextureStorage2D(m_rendererId, 1, format, m_width, m_height); // RGBA8

        glTextureParameteri(m_rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_rendererId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void OpenGLTexture2D::setData(const void* data, size_t size)
    {
        BUBBLE_CORE_ASSERT(static_cast<uint32_t>(size) == m_width * m_height * sizeof(uint32_t), "Different sizes");

        const auto format = m_channels == 3 ? GL_RGB : GL_RGBA;
        glTextureSubImage2D(m_rendererId, 0, 0, 0, m_width, m_height, format, GL_UNSIGNED_BYTE, data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_rendererId);
    }

    void OpenGLTexture2D::bind(uint32_t slot)
    {
        m_slot = slot;
        glActiveTexture(GL_TEXTURE0 + m_slot);
        glBindTexture(GL_TEXTURE_2D, m_rendererId);
    }

    void OpenGLTexture2D::unbind()
    {
        glActiveTexture(GL_TEXTURE0 + m_slot);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    uint32_t OpenGLTexture2D::getRendererId() const
    {
        return m_rendererId;
    }

    bool OpenGLTexture2D::operator==(const Texture& other)
    {
        return m_rendererId == static_cast<const OpenGLTexture2D&>(other).m_rendererId;
    }

} // namespace bubble
