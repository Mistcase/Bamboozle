#include "bubblepch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace bubble
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size, const void* data)
    {
        glCreateBuffers(1, &m_rendererId);
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_rendererId);
    }

    void OpenGLVertexBuffer::setData(const void* data, size_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
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
        glBindBuffer(1, m_rendererId);
    }

    void OpenGLVertexBuffer::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    //----------------------------------------------

    OpenGLIndexBuffer::OpenGLIndexBuffer(size_t count, uint32_t* indices)
        : m_count(count)
    {
        glCreateBuffers(1, &m_rendererId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_rendererId);
    }

    void OpenGLIndexBuffer::setData(uint32_t* indices, size_t count)
    {
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(uint32_t), indices);
    }

    size_t OpenGLIndexBuffer::getCount() const
    {
        return m_count;
    }

    void OpenGLIndexBuffer::bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
    }

    void OpenGLIndexBuffer::unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

} // namespace
