#pragma once

#include <memory>

#include "Butterfly/Renderer/Buffer.h"

namespace butterfly
{
    class VertexArray
    {
    public:
        static Ref<VertexArray> Create();

    public:
        virtual ~VertexArray() = default;

        virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void setIndexBuffer(const Ref<IndexBuffer>& vertexBuffer) = 0;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer> getIndexBuffer() const = 0;
    };

} // namespace butterfly
