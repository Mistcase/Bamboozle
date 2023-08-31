#include "Shaders.h"

#include "Bamboozle/Assert.h"
#include "Bamboozle/Log.h"
#include "Bamboozle/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShaders.h"

namespace bbzl
{
    std::unique_ptr<Shaders> Shaders::Create()
    {
        switch (RenderAPI::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return std::make_unique<OpenGLShaders>();

        default:
            ASSERT_FAIL("Unknown API");
            return nullptr;
        }
    }

} // namespace bbzl
