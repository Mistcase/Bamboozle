#pragma once

#include "Bamboozle/Renderer/Buffer.h"
#include <memory>

namespace bbzl
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

} // namespace bbzl
