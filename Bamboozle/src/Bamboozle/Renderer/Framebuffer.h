#pragma once

#include "Bamboozle/bbzl.h"

namespace bbzl
{
    struct FramebufferSpecification
    {
        uint32_t width;
        uint32_t height;
        uint32_t samples = 1;

        bool isSwapChainTarget = false;
    };

    class Framebuffer
    {
    public:
        static Ref<Framebuffer> Create(const FramebufferSpecification& specification);
        virtual ~Framebuffer();

        virtual void resize(uint32_t width, uint32_t height) = 0;

        virtual const FramebufferSpecification& getSpecification() const = 0;
        virtual uint32_t getColorAttachmentRendererId() const = 0;

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };

} // namespace bbzl
