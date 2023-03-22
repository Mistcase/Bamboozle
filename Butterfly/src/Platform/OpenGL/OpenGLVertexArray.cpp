#include "Butterfly/butterflypch.h"
#include "OpenGLVertexArray.h"

#include "Butterfly/Log.h"

#include <glad/glad.h>

namespace butterfly
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
		switch (type)
		{
		case butterfly::ShaderDataType::Float:
		case butterfly::ShaderDataType::Float2:
		case butterfly::ShaderDataType::Float3:
		case butterfly::ShaderDataType::Float4:
        case butterfly::ShaderDataType::Mat3:
		case butterfly::ShaderDataType::Mat4:
			return GL_FLOAT;

		case butterfly::ShaderDataType::Int:
		case butterfly::ShaderDataType::Int2:
		case butterfly::ShaderDataType::Int3:
		case butterfly::ShaderDataType::Int4:
            return GL_UNSIGNED_INT;

		case butterfly::ShaderDataType::Bool:
			return GL_BOOL;

		default:
			break;
		}

        BUTTERFLY_CORE_ASSERT(false, "Unknown shader data type");
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

        BUTTERFLY_CORE_ASSERT(!vertexBuffer->getLayout().getElements().empty(), "Vertex buffer layout is undefined");

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

		// Why?
		m_vertexBuffers.front()->bind();
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

} // namespace butterfly
