#pragma once

#include "Bubble/Core.h"

#include <string>

namespace bubble
{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const std::string& path);
    };

} // namespace bubble
