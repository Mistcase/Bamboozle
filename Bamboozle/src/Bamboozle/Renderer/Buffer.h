#pragma once

#include "Bamboozle/Ref.h"

#include <cstdint>
#include <string>
#include <vector>

namespace bbzl
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
        BufferLayout(std::initializer_list<BufferElement> elements);

        inline uint32_t getStride() const
        {
            return m_stride;
        }
        inline const Elements& getElements() const
        {
            return m_elements;
        }

        inline Elements::iterator begin()
        {
            return m_elements.begin();
        }
        inline Elements::iterator end()
        {
            return m_elements.end();
        }
        inline Elements::const_iterator begin() const
        {
            return m_elements.begin();
        }
        inline Elements::const_iterator end() const
        {
            return m_elements.end();
        }

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
        static Ref<IndexBuffer> Create(size_t count, const uint32_t* indices = nullptr);

    public:
        virtual ~IndexBuffer() = default;

        virtual void setData(uint32_t* data, size_t count) = 0;

        virtual size_t getCount() const = 0;

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };

} // namespace bbzl
