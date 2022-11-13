#pragma once

#include <memory>

#include "Bubble/Renderer/Buffer.h"

namespace bubble
{
    class VertexArray
    {
    public:
        static VertexArray* Create();

    public:
        virtual ~VertexArray() = default;

        virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void setIndexBuffer(const Ref<IndexBuffer>& vertexBuffer) = 0;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer> getIndexBuffer() const = 0;
    };

} // namespace bubble
