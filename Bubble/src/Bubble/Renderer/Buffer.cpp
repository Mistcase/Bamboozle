#include "bubblepch.h"
#include "Buffer.h"

#include "Bubble/Log.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"

namespace bubble
{
    VertexBuffer* VertexBuffer::Create(float* vertices, size_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None:
            BUBBLE_CORE_ASSERT(false, "Current API is None");
            break;

        case RendererAPI::OpenGL:
            return new OpenGLVertexBuffer(vertices, size);
            break;
        }

        BUBBLE_CORE_ASSERT(false, "Unsupported renderer API");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, size_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None:
            BUBBLE_CORE_ASSERT(false, "Current API is None");
            break;

        case RendererAPI::OpenGL:
            return new OpenGLIndexBuffer(indices, size);
            break;
        }

        BUBBLE_CORE_ASSERT(false, "Unsupported renderer API");
        return nullptr;
    }

} // namespace bubble
