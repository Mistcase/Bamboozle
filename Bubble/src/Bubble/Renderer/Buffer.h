#pragma once

#include <cstdint>

namespace bubble
{
    class VertexBuffer
    {
    public:
        static VertexBuffer* Create(float* vertices, size_t size);

    public:
        virtual ~VertexBuffer() = default;

        // virtual void setData();

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };

    class IndexBuffer
    {
    public:
        static IndexBuffer* Create(uint32_t* indices, size_t size);

    public:
        virtual ~IndexBuffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual size_t getCount() const = 0;
    };

} // namespace bubble
