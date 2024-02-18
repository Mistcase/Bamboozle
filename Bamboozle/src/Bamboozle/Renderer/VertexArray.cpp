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
        case RenderAPI::API_TYPE::None:
            ASSERT(false, "Current API_TYPE is None");
            break;

        case RenderAPI::API_TYPE::OpenGL:
            return std::make_shared<OpenGLVertexArray>();
            break;
        }

        ASSERT(false, "Unsupported renderer API_TYPE");
        return nullptr;
    }

} // namespace bbzl
