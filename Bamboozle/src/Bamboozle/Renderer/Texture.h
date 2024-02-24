#pragma once

#include "Bamboozle/Core.h"
#include <string>

namespace bbzl
{
    class TextureManager;
}

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
		enum Format
		{
			R8,
			R8G8B8,
			R8G8B8A8,

			Count
		};

		static constexpr char* const FormatNames[] = {
			"R8",
			"R8G8B8",
			"R8G8B8A8",
		};

    public:
        static Texture2D* Create(const std::string& path, Format format = Format::R8G8B8);
        static Texture2D* Create(uint32_t width, uint32_t height);

        virtual void setData(const void* data, size_t size) = 0;
        virtual bool operator==(const Texture& other) = 0;

		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;
    };

	static_assert(Texture2D::Format::Count == std::size(Texture2D::FormatNames));

    extern TextureManager* textureManager;

} // namespace bbzl
