#include "Bamboozle/bbzlpch.h"
#include "OpenGLFramebuffer.h"

#include "Bamboozle/bbzl.h"
#include "GlCall.h"

namespace bbzl
{
    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& specification)
        : m_specification(specification)
    {
        invalidate();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
		GL_CALL(glDeleteFramebuffers(1, &m_rendererId));
        GL_CALL(glDeleteTextures(1, &m_colorAttachment));
        GL_CALL(glDeleteTextures(1, &m_depthAttachment));
    }

    void OpenGLFramebuffer::bind()
    {
        GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId));
    }

    void OpenGLFramebuffer::unbind()
    {
        GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }

    void OpenGLFramebuffer::invalidate()
    {
        if (m_rendererId != 0)
        {
            GL_CALL(glDeleteFramebuffers(1, &m_rendererId));
            GL_CALL(glDeleteTextures(1, &m_colorAttachment));
            GL_CALL(glDeleteTextures(1, &m_depthAttachment));
        }

        GL_CALL(glGenFramebuffers(1, &m_rendererId));
        GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId));

		GL_CALL(glGenTextures(1, &m_colorAttachment));
		GL_CALL(glBindTexture(GL_TEXTURE_2D, m_colorAttachment));
		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_specification.width, m_specification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
		GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));

        GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0));

        GL_CALL(glGenTextures(1, &m_depthAttachment));
		GL_CALL(glBindTexture(GL_TEXTURE_2D, m_depthAttachment));
		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_specification.width, m_specification.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr));
		GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthAttachment, 0));

        assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

		GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
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

} // namespace bbzl
