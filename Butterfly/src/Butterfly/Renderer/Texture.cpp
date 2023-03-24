#include "Texture.h"

#include "Butterfly/Log.h"
#include "Butterfly/Renderer/Renderer.h"
#include "Butterfly/butterflypch.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace butterfly
{
    Ref<Texture2D> Texture2D::Create(const std::string& path, Format format)
    {
        assert(format != Format::Count);

        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(path, format);

        default:
            BUTTERFLY_CORE_ASSERT(false, "Unknown RednerAPI provided");
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
            BUTTERFLY_CORE_ASSERT(false, "Unknown RednerAPI provided");
            return nullptr;
        }
    }

} // namespace butterfly
