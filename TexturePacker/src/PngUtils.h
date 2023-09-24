#pragma once

#include "Rect.h"

#include <png.h>
#include <memory>

namespace png_utils
{
	struct Image
	{
        Image();
        
		Image(const Image&) = delete;
		Image(Image&&) = delete;

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
	};

	using ImageHolder = std::unique_ptr<Image>;

	ImageHolder OpenFile(const char* filename);
	bool SaveToFile(const Image& image, const char* filename);

	using Markup = std::vector<Rect>;
	using ImageSet = std::vector<ImageHolder>;
	Image CreateImageByMarkup(size_t width, size_t height, const ImageSet& imageSet, const Markup& markup);

} // namespace Png
