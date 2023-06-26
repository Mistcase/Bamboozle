#pragma once

#include "Bamboozle/Renderer/Framebuffer.h"

namespace bbzl
{
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& specification);
        ~OpenGLFramebuffer();

        void bind() override;
        void unbind() override;

        void invalidate();
        void resize(uint32_t width, uint32_t height) override;

        const FramebufferSpecification& getSpecification() const override;
        uint32_t getColorAttachmentRendererId() const override;

    private:
        uint32_t m_rendererId = 0;
        uint32_t m_colorAttachment = 0;
        uint32_t m_depthAttachment = 0;
        FramebufferSpecification m_specification;
    };

} // namespace bbzl
