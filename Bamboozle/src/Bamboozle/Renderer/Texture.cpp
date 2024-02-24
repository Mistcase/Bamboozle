#include "Bamboozle/bbzlpch.h"
#include "Texture.h"

#include "Bamboozle/Application.h"
#include "Bamboozle/Assert.h"
#include "Bamboozle/Log.h"
#include "Bamboozle/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace bbzl
{
    Texture2D* Texture2D::Create(const std::string& path, Format format)
    {
        ASSERT(format != Format::Count);

        switch (Renderer::GetAPI())
        {
        case RenderAPI::API_TYPE::OpenGL:
            return new OpenGLTexture2D(path, format);
            
        default:
            ASSERT_FAIL("Unknown RednerAPI provided");
            return nullptr;
        }
    }

    Texture2D* Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API_TYPE::OpenGL:
            return new OpenGLTexture2D(width, height);

        default:
            ASSERT_FAIL("Unknown RednerAPI provided");
            return nullptr;
        }
    }

} // namespace bbzl
