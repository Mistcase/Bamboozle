#include "bubblepch.h"
#include "VertexArray.h"

#include "Bubble/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace bubble
{
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None:
            BUBBLE_CORE_ASSERT(false, "Current API is None");
            break;

        case RendererAPI::OpenGL:
            return new OpenGLVertexArray();
            break;
        }

        BUBBLE_CORE_ASSERT(false, "Unsupported renderer API");
        return nullptr;
    }

} // namespace bubble
