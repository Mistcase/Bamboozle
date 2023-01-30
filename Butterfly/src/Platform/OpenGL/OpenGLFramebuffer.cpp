#include "Butterfly/butterflypch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace butterfly
{
    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& specification)
        : m_specification(specification)
    {
        invalidate();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        glDeleteFramebuffers(1, &m_rendererId);
        glDeleteTextures(1, &m_colorAttachment);
        glDeleteTextures(1, &m_depthAttachment);
    }

    void OpenGLFramebuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);
    }

    void OpenGLFramebuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::invalidate()
    {
        if (m_rendererId != 0)
        {
            glDeleteFramebuffers(1, &m_rendererId);
            glDeleteTextures(1, &m_colorAttachment);
            glDeleteTextures(1, &m_depthAttachment);
        }

		glGenFramebuffers(1, &m_rendererId); // glCreateFramebuffers(1, &m_rendererId);
        glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);

		glGenTextures(1, &m_colorAttachment); //glCreateTextures(GL_TEXTURE_2D, 1, &m_colorAttachment);
        glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_specification.width, m_specification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);

        glGenTextures(1, &m_depthAttachment); // glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachment);
        glBindTexture(GL_TEXTURE_2D, m_depthAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_specification.width, m_specification.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
        // glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_specification.width, m_specification.height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0);

        BUTTERFLY_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::resize(uint32_t width, uint32_t height)
    {
        m_specification.width = width;
        m_specification.height = height;

        invalidate();
    }

    const FramebufferSpecification& OpenGLFramebuffer::getSpecification() const
    {
        return m_specification;
    }

    uint32_t OpenGLFramebuffer::getColorAttachmentRendererId() const
    {
        return m_colorAttachment;
    }

} // namespace butterfly
