#include "Bamboozle/bbzlpch.h"
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
        case RenderAPI::API_TYPE::None:
            ASSERT_FAIL("API_TYPE is None");
            break;

        case RenderAPI::API_TYPE::OpenGL:
            return std::make_shared<OpenGLUniformBuffer>(size);
            break;
        }

        ASSERT_FAIL("Unsupported renderer API_TYPE");
        return nullptr;
    }

} // namespace bbzl
