#pragma once

#include "Bubble/Renderer/Buffer.h"

namespace bubble
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, size_t size);
        ~OpenGLVertexBuffer() override;

        void bind() override;
        void unbind() override;

    private:
        uint32_t m_rendererId;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, size_t count);
        ~OpenGLIndexBuffer() override;

        void bind() override;
        void unbind() override;

        size_t getCount() const override;

    private:
        size_t m_count;
        uint32_t m_rendererId;
    };

} // namespace
