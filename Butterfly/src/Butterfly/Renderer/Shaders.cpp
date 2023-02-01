#include "Butterfly/butterflypch.h"
#include "Shaders.h"

#include "Butterfly/Log.h"
#include "Butterfly/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShaders.h"

namespace butterfly
{
    std::unique_ptr<Shaders> Shaders::Create()
    {
        switch (RenderAPI::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return std::make_unique<OpenGLShaders>();

        default:
            BUTTERFLY_CORE_ASSERT(false, "Unknown API");
            return nullptr;
        }
    }

} // namespace butterfly
