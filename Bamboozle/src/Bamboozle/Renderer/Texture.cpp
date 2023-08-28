#include "Texture.h"

#include "Bamboozle/Log.h"
#include "Bamboozle/Renderer/Renderer.h"
#include "Bamboozle/bbzl.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace bbzl
{
    Texture2D* Texture2D::Create(const std::string& path, Format format)
    {
        assert(format != Format::Count);

        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return new OpenGLTexture2D(path, format);

        default:
            BBZL_CORE_ASSERT(false, "Unknown RednerAPI provided");
            return nullptr;
        }
    }

    Texture2D* Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return new OpenGLTexture2D(width, height);

        default:
            BBZL_CORE_ASSERT(false, "Unknown RednerAPI provided");
            return nullptr;
        }
    }

} // namespace bbzl
