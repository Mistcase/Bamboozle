#include "UniformBuffer.h"

#include "Bamboozle/Renderer/Renderer.h"
#include "Bamboozle/bbzl.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace bbzl
{
    Ref<UniformBuffer> UniformBuffer::Create(size_t size)
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::None:
            assert(!"API is None");
            break;

        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLUniformBuffer>(size);
            break;
        }

        assert(!"Unsupported renderer API");
        return nullptr;
    }

} // namespace bbzl
