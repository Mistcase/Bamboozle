#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Butterfly/Log.h"

namespace butterfly
{
    enum class ShaderDataType : uint8_t
    {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool
    };

    static size_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch(type)
        {
        case ShaderDataType::Float: return 4;
        case ShaderDataType::Float2: return 8;
        case ShaderDataType::Float3: return 12;
        case ShaderDataType::Float4: return 16;
        case ShaderDataType::Mat3: return 4 * 3 * 3;
        case ShaderDataType::Mat4: return 4 * 4 *  4;
        case ShaderDataType::Int: return 4;
        case ShaderDataType::Int2: return 8;
        case ShaderDataType::Int3: return 12;
        case ShaderDataType::Int4: return 16;
        case ShaderDataType::Bool: return 1;

        default:
            break;
        }

        BUTTERFLY_CORE_ASSERT(false, "Unknown shader type");
        return 0;
    }

    struct BufferElement
    {
        std::string name;
        size_t size = 0;
        uint32_t offset = 0;
        ShaderDataType type;
        bool normalized;

        BufferElement(ShaderDataType _type, const std::string& _name, bool normalized = false);
        size_t getComponentCount() const;
    };

    class BufferLayout
    {
    public:
        using Elements = std::vector<BufferElement>;

    public:
        BufferLayout() = default;
        BufferLayout(const std::initializer_list<BufferElement>& elements);

        inline uint32_t getStride() const { return m_stride; }
        inline const Elements& getElements() const { return m_elements; }

        inline Elements::iterator begin() { return m_elements.begin(); }
		inline Elements::iterator end() { return m_elements.end(); }
        inline Elements::const_iterator begin() const  { return m_elements.begin(); }
		inline Elements::const_iterator end() const { return m_elements.end(); }

    private:
        void calculateOffsetsAndStride();

    private:
        Elements m_elements;
        uint32_t m_stride;
    };

    class VertexBuffer
    {
    public:
        static Ref<VertexBuffer> Create(size_t size, void* data = nullptr);

    public:
        virtual ~VertexBuffer() = default;

        virtual const BufferLayout& getLayout() const = 0;
        virtual void setLayout(const BufferLayout& layout) = 0;
        virtual void setData(const void* data, size_t size) = 0;

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };

    class IndexBuffer
    {
    public:
        static Ref<IndexBuffer> Create(size_t count, uint32_t* indices = nullptr);

    public:
        virtual ~IndexBuffer() = default;

        virtual void setData(uint32_t* data, size_t count) = 0;

        virtual size_t getCount() const = 0;

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };

} // namespace butterfly
