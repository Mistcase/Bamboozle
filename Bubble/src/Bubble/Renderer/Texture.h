#pragma once

#include "Bubble/Core.h"

#include <string>

namespace bubble
{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual void bind(uint32_t slot) = 0;
        virtual void unbind() = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const std::string& path);
        static Ref<Texture2D> Create(uint32_t width, uint32_t height);

        virtual void setData(const void* data, size_t size) = 0;

        virtual bool operator==(const Texture& other) = 0;
    };

} // namespace bubble
