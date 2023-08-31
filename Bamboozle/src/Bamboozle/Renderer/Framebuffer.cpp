#include "Framebuffer.h"

#include "Bamboozle/Assert.h"
#include "Bamboozle/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace bbzl
{
    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specification)
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLFramebuffer>(specification);

        default:
            ASSERT_FAIL("Unsupported render api was provided");
            return nullptr;
        }
    }

    Framebuffer::~Framebuffer() = default;

} // namespace bbzl
