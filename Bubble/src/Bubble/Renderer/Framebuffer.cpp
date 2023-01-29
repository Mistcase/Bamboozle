#include "Bubble/bubblepch.h"
#include "Framebuffer.h"

#include "Bubble/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace bubble
{
    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specification)
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLFramebuffer>(specification);

        default:
            BUBBLE_CORE_ASSERT(false, "Unsupported render api was provided");
            return nullptr;
        }
    }

    Framebuffer::~Framebuffer() = default;
} // namespace bubble
