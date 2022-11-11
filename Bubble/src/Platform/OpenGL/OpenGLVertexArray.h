#pragma once

#include "Bubble/Renderer/VertexArray.h"

namespace bubble
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() override;

        void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        void bind() const override;
        void unbind() const override;

        const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override;
        const std::shared_ptr<IndexBuffer> getIndexBuffer() const override;

    private:
        std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
        std::shared_ptr<IndexBuffer> m_indexBuffer;

        uint32_t m_rendererId;
    };

} // namespace bubble
