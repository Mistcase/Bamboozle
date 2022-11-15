#pragma once

#include <string>
#include <filesystem>

#include "Bubble/Core.h"

namespace bubble
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual const char* getName() const = 0;
    };

} // namespace bubble
