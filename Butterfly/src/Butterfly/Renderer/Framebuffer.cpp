#include "Butterfly/butterflypch.h"
#include "Framebuffer.h"

#include "Butterfly/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace butterfly
{
    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specification)
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLFramebuffer>(specification);

        default:
            BUTTERFLY_CORE_ASSERT(false, "Unsupported render api was provided");
            return nullptr;
        }
    }

    Framebuffer::~Framebuffer() = default;
} // namespace butterfly
