#pragma once

#include "Bamboozle/Core.h"
#include <string>

namespace bbzl
{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual void bind(uint32_t slot) const = 0;
        virtual void unbind() const = 0;

        virtual uint32_t getRendererId() const = 0;
    };

    class Texture2D : public Texture
    {
	public:
		enum class Format
		{
			RED,
			RGB,
			RGBA,

			Count
		};

    public:
        static Texture2D* Create(const std::string& path, Format format = Format::RGB);
        static Texture2D* Create(uint32_t width, uint32_t height);

        virtual void setData(const void* data, size_t size) = 0;
        virtual bool operator==(const Texture& other) = 0;
    };

} // namespace bbzl
