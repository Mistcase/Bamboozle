#pragma once

#include <string>
#include <filesystem>

#include "Butterfly/Core.h"

namespace butterfly
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual const char* getName() const = 0;
    };

} // namespace butterfly
