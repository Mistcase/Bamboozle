#pragma once

#include <string>

#include "Bubble/Core.h"

namespace bubble
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static Ref<Shader> Create(const std::string& srcVertex, const std::string& srcFragment);
    private:
        uint32_t m_rendererId;
    };

} // namespace bubble
