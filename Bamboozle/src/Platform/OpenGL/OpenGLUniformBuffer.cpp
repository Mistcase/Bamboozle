#include "Bamboozle/bbzlpch.h"
#include "OpenGLUniformBuffer.h"

#include "Bamboozle/bbzl.h"
#include "GlCall.h"

namespace bbzl
{
    OpenGLUniformBuffer::OpenGLUniformBuffer(size_t size)
    {
        GL_CALL(glGenBuffers(1, &m_rendererId));
        GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, m_rendererId));
        GL_CALL(glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW));
    }

    void OpenGLUniformBuffer::bind(uint32_t bindPoint) const
    {
        GL_CALL(glBindBufferBase(GL_UNIFORM_BUFFER, bindPoint, m_rendererId));
    }

    void OpenGLUniformBuffer::bind() const
    {
        GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, m_rendererId));
    }

    void OpenGLUniformBuffer::unbind() const
    {
        GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, 0));
    }

    void OpenGLUniformBuffer::submit(const void* data, size_t size) const
    {
        assert(data != nullptr);
        GL_CALL(glBindBuffer(GL_UNIFORM_BUFFER, m_rendererId));
        GL_CALL(glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data));
    }

} // namespace bbzl
