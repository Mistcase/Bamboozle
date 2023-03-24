#pragma once

#include "Butterfly/Renderer/UniformBuffer.h"

namespace butterfly
{
    class OpenGLUniformBuffer : public UniformBuffer
    {
    public:
        OpenGLUniformBuffer(size_t size);

        void bind(uint32_t bindPoint) const override;
        void bind() const override;
        void unbind() const override;

        void submit(const void* data, size_t size) const override;

    private:
        uint32_t m_rendererId;
    };

} // namespace butterfly
