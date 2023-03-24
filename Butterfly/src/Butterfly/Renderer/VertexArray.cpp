#include "VertexArray.h"

#include "Butterfly/Renderer/Renderer.h"
#include "Butterfly/butterflypch.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace butterfly
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::None:
            BUTTERFLY_CORE_ASSERT(false, "Current API is None");
            break;

        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexArray>();
            break;
        }

        BUTTERFLY_CORE_ASSERT(false, "Unsupported renderer API");
        return nullptr;
    }

} // namespace butterfly
