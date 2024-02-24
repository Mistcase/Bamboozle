#include "OpenGLTexture.h"

#include "Bamboozle/Assert.h"
#include "Bamboozle/Log.h"
#include "Bamboozle/bbzl.h"
#include "GlCall.h"

#include <stb_image.h>

namespace
{
    int FormatMappings[] = {
        GL_RED,
        GL_RGB,
        GL_RGBA
    };

} // namespace

namespace bbzl
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path, Format format)
    {
        BBZL_CORE_INFO("Creating 2D texture: {}", path);

        GL_CALL(glGenTextures(1, &m_rendererId));
        GL_CALL(glActiveTexture(GL_TEXTURE0));
		GL_CALL(glBindTexture(GL_TEXTURE_2D, m_rendererId));

        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        // stbi_set_flip_vertically_on_load(1);

        int width, height, channels;
        auto data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        assert(data != nullptr);
        assert((channels == 3 && format == Format::R8G8B8) ||
               (channels == 4 && format == Format::R8G8B8A8) ||
               (channels == 1 && format == Format::R8));

        m_width = static_cast<uint32_t>(width);
        m_height = static_cast<uint32_t>(height);
        m_channels = static_cast<uint32_t>(channels);

        const auto textureFormat = FormatMappings[static_cast<size_t>(format)];
        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, m_width, m_height, 0, textureFormat, GL_UNSIGNED_BYTE, data));

        stbi_image_free(data);
    }

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : m_width(width)
        , m_height(height)
    {
        GL_CALL(glGenTextures(1, &m_rendererId));
		GL_CALL(glActiveTexture(GL_TEXTURE0));
		GL_CALL(glBindTexture(GL_TEXTURE_2D, m_rendererId));

        const auto internalFormat = m_channels == 3 ? GL_RGB8 : GL_RGBA8;
        const auto format = internalFormat == GL_RGB8 ? GL_RGB : GL_RGBA;

        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, nullptr));

        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    }

    void OpenGLTexture2D::setData(const void* data, size_t size)
    {
        ASSERT(static_cast<uint32_t>(size) == m_width * m_height * sizeof(uint32_t), "Different sizes");

        const auto format = m_channels == 3 ? GL_RGB : GL_RGBA;
        GL_CALL(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, format, GL_UNSIGNED_BYTE, data));
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        GL_CALL(glDeleteTextures(1, &m_rendererId));
    }

    void OpenGLTexture2D::bind(uint32_t slot) const
    {
        m_slot = slot;
        GL_CALL(glActiveTexture(GL_TEXTURE0 + m_slot));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, m_rendererId));
    }

    void OpenGLTexture2D::unbind() const
    {
        GL_CALL(glActiveTexture(GL_TEXTURE0 + m_slot));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
    }

    uint32_t OpenGLTexture2D::getRendererId() const
    {
        return m_rendererId;
    }

	int OpenGLTexture2D::getWidth() const
	{
		return m_width;
	}

	int OpenGLTexture2D::getHeight() const
	{
		return m_height;
	}

    bool OpenGLTexture2D::operator==(const Texture& other)
    {
        return m_rendererId == static_cast<const OpenGLTexture2D&>(other).m_rendererId;
    }

} // namespace bbzl
