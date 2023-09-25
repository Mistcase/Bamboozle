#pragma once

#include "Rect.h"

#include <png.h>
#include <memory>
#include <vector>

namespace png_utils
{
	struct Image
	{
        Image();
		Image(Image&& other);

		Image(const Image&) = delete;

		Image& operator=(const Image&) = delete;
		Image& operator=(Image&&) = delete;

		~Image()
		{
			if (rowPointers == nullptr)
			{
				return;
			}

			for (size_t i = 0; i < height; ++i)
			{
				free(rowPointers[i]);
			}

			free(rowPointers);
		}

		size_t width = 0;
		size_t height = 0;
		size_t depth = 0; // in bits
		png_bytep *rowPointers = nullptr;
		int colorType;
	};

	using ImageHolder = std::unique_ptr<Image>;
	using ImageSet = std::vector<ImageHolder>;
	using Markup = std::vector<Rect>;

	ImageHolder OpenFile(const char* filename);
	bool SaveToFile(const char* filename, const Image& image);

	Image CreateImageByMarkup(const ImageSet& images, const Markup& markup, int outWidth, int outHeight);

} // namespace png_utils
