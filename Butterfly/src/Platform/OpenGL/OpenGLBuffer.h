#pragma once

#include "Butterfly/Renderer/Buffer.h"

namespace butterfly
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(size_t size, const void* data);
        ~OpenGLVertexBuffer() override;

        void setData(const void* data, size_t size) override;

        const BufferLayout& getLayout() const override;
        void setLayout(const BufferLayout& layout) override;

        void bind() override;
        void unbind() override;

    private:
        BufferLayout m_layout;

    private:
        uint32_t m_rendererId;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(size_t count, const uint32_t* indices);
        ~OpenGLIndexBuffer() override;

        void setData(uint32_t* indices, size_t count) override;

        size_t getCount() const override;

        void bind() override;
        void unbind() override;

    private:
        size_t m_count;
        uint32_t m_rendererId;
    };

} // namespace
