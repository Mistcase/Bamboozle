#pragma once

#include "Butterfly/Renderer/VertexArray.h"

namespace butterfly
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() override;

        void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
        void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

        void bind() const override;
        void unbind() const override;

        const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override;
        const Ref<IndexBuffer> getIndexBuffer() const override;

    private:
        std::vector<Ref<VertexBuffer>> m_vertexBuffers;
        Ref<IndexBuffer> m_indexBuffer;

        uint32_t m_rendererId;
    };

} // namespace butterfly
