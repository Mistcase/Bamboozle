#include "Butterfly/butterflypch.h"
#include "Buffer.h"

#include "Butterfly/Log.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"

namespace butterfly
{
    BufferElement::BufferElement(ShaderDataType _type, const std::string& _name, bool _normalized)
        : name(_name)
        , size(ShaderDataTypeSize(_type))
        , type(_type)
        , normalized(_normalized)
    {
    }

    size_t BufferElement::getComponentCount() const
    {
        switch (type)
        {
        case ShaderDataType::Float:  return 1;
        case ShaderDataType::Float2: return 2;
        case ShaderDataType::Float3: return 3;
        case ShaderDataType::Float4: return 4;
        case ShaderDataType::Mat3:   return 3 * 3;
        case ShaderDataType::Mat4:   return 4 * 4;
        case ShaderDataType::Int:    return 1;
        case ShaderDataType::Int2:   return 2;
        case ShaderDataType::Int3:   return 3;
        case ShaderDataType::Int4:   return 4;
        case ShaderDataType::Bool:   return 1;

        default:
            break;
        }

        BUTTERFLY_CORE_ASSERT(false, "Unknown shader data type");
        return 0;
    }

    BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements)
        : m_elements(elements)
    {
        calculateOffsetsAndStride();
    }

    void BufferLayout::calculateOffsetsAndStride()
    {
        uint32_t offset = 0;
        m_stride = 0;

        for (auto& element : m_elements)
        {
            element.offset = offset;
            offset += static_cast<uint32_t>(element.size);
            m_stride += static_cast<uint32_t>(element.size);
        }
    }

    Ref<VertexBuffer> VertexBuffer::Create(size_t size, void* data)
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::None:
            BUTTERFLY_CORE_ASSERT(false, "Current API is None");
            break;

        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(size, data);
            break;
        }

        BUTTERFLY_CORE_ASSERT(false, "Unsupported renderer API");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(size_t count, const uint32_t* indices)
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::None:
            BUTTERFLY_CORE_ASSERT(false, "Current API is None");
            break;

        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLIndexBuffer>(count, indices);
            break;
        }

        BUTTERFLY_CORE_ASSERT(false, "Unsupported renderer API");
        return nullptr;
    }

} // namespace butterfly
