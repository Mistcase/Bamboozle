#include "OpenGLVertexArray.h"

#include "Bamboozle/Log.h"
#include "Bamboozle/bbzl.h"
#include <glad/glad.h>

namespace bbzl
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case bbzl::ShaderDataType::Float:
        case bbzl::ShaderDataType::Float2:
        case bbzl::ShaderDataType::Float3:
        case bbzl::ShaderDataType::Float4:
        case bbzl::ShaderDataType::Mat3:
        case bbzl::ShaderDataType::Mat4:
            return GL_FLOAT;

        case bbzl::ShaderDataType::Int:
        case bbzl::ShaderDataType::Int2:
        case bbzl::ShaderDataType::Int3:
        case bbzl::ShaderDataType::Int4:
            return GL_UNSIGNED_INT;

        case bbzl::ShaderDataType::Bool:
            return GL_BOOL;

        default:
            break;
        }

        BBZL_CORE_ASSERT(false, "Unknown shader data type");
        return 0;
    };

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_rendererId);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_rendererId);
    }

    void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        glBindVertexArray(m_rendererId);
        vertexBuffer->bind();

        BBZL_CORE_ASSERT(!vertexBuffer->getLayout().getElements().empty(), "Vertex buffer layout is undefined");

        int index = 0;
        const auto& layout = vertexBuffer->getLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                                  (GLuint)element.getComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.type),
                                  element.normalized ? GL_TRUE : GL_FALSE,
                                  layout.getStride(),
                                  ((const void*)(size_t)element.offset));
            index++;
        }

        m_vertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_rendererId);
        indexBuffer->bind();

        m_indexBuffer = indexBuffer;
    }

    void OpenGLVertexArray::bind() const
    {
        glBindVertexArray(m_rendererId);

        if (m_indexBuffer != nullptr)
            m_indexBuffer->bind();
    }

    void OpenGLVertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

    const std::vector<Ref<VertexBuffer>>& OpenGLVertexArray::getVertexBuffers() const
    {
        return m_vertexBuffers;
    }

    const Ref<IndexBuffer> OpenGLVertexArray::getIndexBuffer() const
    {
        return m_indexBuffer;
    }

} // namespace bbzl
