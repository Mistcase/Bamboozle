#pragma once

#include "Butterfly/Core.h"
#include <filesystem>
#include <string>

namespace butterfly
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void bindUniformBlock(const char* blockName, uint32_t bindPoint) const = 0;
        virtual void setSampler(const char* sampler, uint32_t value) const = 0;

        virtual const char* getName() const = 0;
    };

} // namespace butterfly
