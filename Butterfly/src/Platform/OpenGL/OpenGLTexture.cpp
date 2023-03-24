#include "OpenGLTexture.h"

#include "Butterfly/Log.h"
#include "Butterfly/butterflypch.h"
#include <glad/glad.h>
#include <stb_image.h>

namespace butterfly
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
    {
        BUTTERFLY_CORE_INFO("Creating 2D texture: {}", path);

        glGenTextures(1, &m_rendererId);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_rendererId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        stbi_set_flip_vertically_on_load(1);

        int width, height, channels;
        auto data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        assert(data != nullptr);

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
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void OpenGLTexture2D::setData(const void* data, size_t size)
    {
        BUTTERFLY_CORE_ASSERT(static_cast<uint32_t>(size) == m_width * m_height * sizeof(uint32_t), "Different sizes");

        const auto format = m_channels == 3 ? GL_RGB : GL_RGBA;
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, format, GL_UNSIGNED_BYTE, data);
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

} // namespace butterfly
