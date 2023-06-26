#include "VertexArray.h"

#include "Bamboozle/Renderer/Renderer.h"
#include "Bamboozle/bbzl.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace bbzl
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::None:
            BBZL_CORE_ASSERT(false, "Current API is None");
            break;

        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexArray>();
            break;
        }

        BBZL_CORE_ASSERT(false, "Unsupported renderer API");
        return nullptr;
    }

} // namespace bbzl
