#include "Bamboozle/bbzlpch.h"
#include "VertexLayout.h"

#include "Buffer.h"

namespace bbzl
{
    static size_t ShaderDataTypeSize(VertexElementDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:
            return 4;
        case ShaderDataType::Float2:
            return 8;
        case ShaderDataType::Float3:
            return 12;
        case ShaderDataType::Float4:
            return 16;
        case ShaderDataType::Mat3:
            return 4 * 3 * 3;
        case ShaderDataType::Mat4:
            return 4 * 4 * 4;
        case ShaderDataType::Int:
            return 4;
        case ShaderDataType::Int2:
            return 8;
        case ShaderDataType::Int3:
            return 12;
        case ShaderDataType::Int4:
            return 16;
        case ShaderDataType::Bool:
            return 1;

        default:
            break;
        }

        ASSERT(false, "Unknown shader type");
        return 0;
    }

    VertexBufferElement::VertexBufferElement(VertexElementDataType _type, const std::string& _name, bool normalized)
        : name(_name)
        , size(ShaderDataTypeSize(_type))
        , type(_type)
        , normalized(normalized)
    {
    }

    size_t VertexBufferElement::getComponentCount() const
    {
        switch (type)
        {
        case ShaderDataType::Float:
            return 1;
        case ShaderDataType::Float2:
            return 2;
        case ShaderDataType::Float3:
            return 3;
        case ShaderDataType::Float4:
            return 4;
        case ShaderDataType::Mat3:
            return 3 * 3;
        case ShaderDataType::Mat4:
            return 4 * 4;
        case ShaderDataType::Int:
            return 1;
        case ShaderDataType::Int2:
            return 2;
        case ShaderDataType::Int3:
            return 3;
        case ShaderDataType::Int4:
            return 4;
        case ShaderDataType::Bool:
            return 1;

        default:
            break;
        }

        ASSERT(false, "Unknown shader data type");
        return 0;
    }

    VertexLayout::VertexLayout(std::initializer_list<VertexBufferElement> elements)
        : m_elements(elements)
    {
        calculateOffsetsAndStride();
    }

    void VertexLayout::calculateOffsetsAndStride()
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
}
