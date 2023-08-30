#include "OpenGLBuffer.h"

#include "Bamboozle/bbzl.h"
#include "GlCall.h"

namespace bbzl
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size, const void* data)
    {
        GL_CALL(glGenBuffers(1, &m_rendererId));
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        GL_CALL(glDeleteBuffers(1, &m_rendererId));
    }

    void OpenGLVertexBuffer::setData(const void* data, size_t size)
    {
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
        GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
    }

    const BufferLayout& OpenGLVertexBuffer::getLayout() const
    {
        return m_layout;
    }

    void OpenGLVertexBuffer::setLayout(const BufferLayout& layout)
    {
        m_layout = layout;
    }

    void OpenGLVertexBuffer::bind()
    {
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererId));
    }

    void OpenGLVertexBuffer::unbind()
    {
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    //----------------------------------------------

    OpenGLIndexBuffer::OpenGLIndexBuffer(size_t count, const uint32_t* indices)
        : m_count(count)
    {
        GL_CALL(glGenBuffers(1, &m_rendererId));
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
		GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW));
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        GL_CALL(glDeleteBuffers(1, &m_rendererId));
    }

    void OpenGLIndexBuffer::setData(uint32_t* indices, size_t count)
    {
        GL_CALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(uint32_t), indices));
    }

    size_t OpenGLIndexBuffer::getCount() const
    {
        return m_count;
    }

    void OpenGLIndexBuffer::bind()
    {
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId));
    }

    void OpenGLIndexBuffer::unbind()
    {
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

} // namespace bbzl
