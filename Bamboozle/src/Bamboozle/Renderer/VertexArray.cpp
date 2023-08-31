#include "VertexArray.h"

#include "Bamboozle/Assert.h"
#include "Bamboozle/bbzl.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace bbzl
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::None:
            ASSERT(false, "Current API is None");
            break;

        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexArray>();
            break;
        }

        ASSERT(false, "Unsupported renderer API");
        return nullptr;
    }

} // namespace bbzl
