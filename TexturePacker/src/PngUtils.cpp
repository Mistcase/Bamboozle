#include "PngUtils.h"

namespace png_utils
{
    Image::Image() = default;

	Image::Image(Image&& other)
		: width(other.width)
		, height(other.height)
		, depth(other.depth)
		, rowPointers(other.rowPointers)
		, colorType(other.colorType)
	{
		other.rowPointers = nullptr;
	}

	std::unique_ptr<Image> OpenFile(const char* filename)
	{
		FILE *fp = fopen(filename, "rb");

		png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if(!png)
		{
			abort();
		}

		png_infop info = png_create_info_struct(png);
		if(!info)
		{
			abort();
		}

		if(setjmp(png_jmpbuf(png)))
		{
			abort();
		}

		png_init_io(png, fp);

		png_read_info(png, info);

		auto image = std::make_unique<Image>();
		image->width = png_get_image_width(png, info);
		image->height = png_get_image_height(png, info);

		const auto color_type = png_get_color_type(png, info);
		const auto bit_depth  = png_get_bit_depth(png, info);

		// Read any color_type into 8bit depth, RGBA format.
		// See http://www.libpng.org/pub/png/libpng-manual.txt

		if(bit_depth == 16)
			png_set_strip_16(png);

		if(color_type == PNG_COLOR_TYPE_PALETTE)
			png_set_palette_to_rgb(png);


		// PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
		if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
			png_set_expand_gray_1_2_4_to_8(png);

		if(png_get_valid(png, info, PNG_INFO_tRNS))
			png_set_tRNS_to_alpha(png);

		// These color_type don't have an alpha channel then fill it with 0xff.
		if(color_type == PNG_COLOR_TYPE_RGB ||
		   color_type == PNG_COLOR_TYPE_GRAY ||
		   color_type == PNG_COLOR_TYPE_PALETTE)
			png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

		if(color_type == PNG_COLOR_TYPE_GRAY ||
		   color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
			png_set_gray_to_rgb(png);

		png_read_update_info(png, info);

		if (image->rowPointers)
		{
			abort();
		}

		image->rowPointers = (png_bytep*)malloc(sizeof(png_bytep) * image->height);
		for(int y = 0; y < image->height; y++) {
			image->rowPointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
		}

		png_read_image(png, image->rowPointers);

		fclose(fp);

		png_destroy_read_struct(&png, &info, NULL);

		return image;
	}

	bool SaveToFile(const char* filename, const Image& image)
	{
		auto* rowPointers = image.rowPointers;
		if (!rowPointers)
		{
			return false;
		}

		int y;
		FILE *fp = fopen(filename, "wb");
		if(!fp)
		{
			return false;
		}

		png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png)
		{
			return false;
		}

		png_infop info = png_create_info_struct(png);
		if (!info)
		{
			return false;
		}

		if (setjmp(png_jmpbuf(png))) abort();

		png_init_io(png, fp);

		const auto width = image.width;
		const auto height = image.height;

		// Output is 8bit depth, RGBA format.
		png_set_IHDR(
			png,
			info,
			width, height,
			8,
			PNG_COLOR_TYPE_RGBA,
			PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_DEFAULT,
			PNG_FILTER_TYPE_DEFAULT
			);
		png_write_info(png, info);

		// To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
		// Use png_set_filler().
		//png_set_filler(png, 0, PNG_FILLER_AFTER);

		png_write_image(png, rowPointers);
		png_write_end(png, NULL);

		fclose(fp);

		png_destroy_write_struct(&png, &info);

		return true;
	}

	Image CreateImageByMarkup(const ImageSet& images, const Markup& markup, int outWidth, int outHeight)
	{
		if (images.empty())
		{
			return {};
		}

		if (images.size() != markup.size())
		{
			return {};
		}

		const auto& first = images.front();

		// Create a new image object for the output image
		Image outImg;
		outImg.width = outWidth;
		outImg.height = outHeight;
		outImg.colorType = first->colorType;
		outImg.depth = first->depth;

		outImg.rowPointers = (png_bytep*)malloc(sizeof(png_bytep) * outImg.height);
		for(int y = 0; y < outImg.height; y++)
		{
			outImg.rowPointers[y] = (png_byte*)malloc(sizeof(png_byte) * outImg.width * 4); // Assuming RGBA format
			memset(outImg.rowPointers[y], 0, sizeof(png_byte) * outImg.width * 4); // Initialize with transparency
		}

		for (size_t i = 0, size = images.size(); i < size; ++i)
		{
			const auto& img = images[i];
			const auto& rect = markup[i];

			const auto width = rect.getWidth();
			const auto height = rect.getHeight();

			// Check if image fits into the output image
			if(rect.l < 0 || rect.t < 0 || rect.l + width > outWidth || rect.t + height > outHeight)
			{
				return {}; // This image would not fit in the output image, return false
			}

			for(int y = 0; y < height; y++)
			{
				memcpy(outImg.rowPointers[y + rect.t] + rect.l * 4, img->rowPointers[y], sizeof(png_byte) * width * 4);
			}
		}

		return outImg;
	}

} // namespace png_utils
