#include "bubblepch.h"
#include "Shaders.h"

#include "Bubble/Log.h"
#include "Bubble/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShaders.h"

namespace bubble
{
    std::unique_ptr<Shaders> Shaders::Create()
    {
        switch (RenderAPI::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return std::make_unique<OpenGLShaders>();

        default:
            BUBBLE_CORE_ASSERT(false, "Unknown API");
            return nullptr;
        }
    }

} // namespace bubble
