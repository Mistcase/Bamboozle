#include "bubblepch.h"
#include "Texture.h"

#include "Bubble/Renderer/Renderer.h"
#include "Bubble/Log.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace bubble
{
    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(path);

        default:
            BUBBLE_CORE_ASSERT(false, "Unknown RednerAPI provided");
            return nullptr;
        }
    }

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(width, height);

        default:
            BUBBLE_CORE_ASSERT(false, "Unknown RednerAPI provided");
            return nullptr;
        }
    }

} // namespace bubble
