#include "Packer.h"

#include "PngUtils.h"
#include "Rect.h"

#include <filesystem>

namespace
{
	class AtlasMarkup
	{
	public:
		using Layout = std::vector<Rect>;

	public:
		AtlasMarkup(size_t width, size_t height)
		{
			m_availableRects.emplace_back(0, 0, width, height);
		}

		bool accureRect(size_t width, size_t height)
		{
			for (size_t i = 0, size = m_availableRects.size(); i < size; ++i)
			{
				const auto idx = size - i - 1;
				const auto rect = m_availableRects[idx];

				const auto rectWidth = rect.getWidth();
				const auto rectHeight = rect.getHeight();

				if (rectWidth >= width && rectHeight >= height)
				{
					const auto x2 = rect.l + width;
					const auto y2 = rect.t + height;

					m_availableRects[idx] = m_availableRects.back();
					m_availableRects.pop_back();

					m_availableRects.emplace_back(x2, rect.t, rect.r, y2);
					m_availableRects.emplace_back(rect.l, rect.t + height, rect.r, rect.b);

					m_usedRects.emplace_back(rect.l, rect.t, x2, y2);

					return true;
				}
			}

			return false;
		}

		const Layout& getLayout() const { return m_usedRects; }

	private:
		Layout m_availableRects;
		Layout m_usedRects;

		size_t m_width;
		size_t m_height;
	};

	constexpr size_t AtlasTextureWidth = 2048;
	constexpr size_t AtlasTextureHeight = 2048;

} // namespace

Packer::Packer(const AtlasDescList& atlasDescs, const char* outputDirectory)
	: m_atlasDescs(atlasDescs)
	, m_outputDirectory(outputDirectory)
{
}

void Packer::generateAtlases() const
{
	// Output for each atlas:
	// 1. Atlas file (just pasted together source images)
	// 2. Desc file with sprites makring

	std::filesystem::path outputDir(m_outputDirectory);
	for (const auto& desc : m_atlasDescs)
	{
		const auto atlasFolderPath = outputDir/desc.name;
		std::filesystem::remove(atlasFolderPath);

		const auto created = std::filesystem::create_directory(atlasFolderPath);
		if (!created)
		{
			// TODO: Throw smth?

			printf("Error: directory for atlas %s is not created\n", atlasFolderPath.c_str());
			continue;
		}

		// Create layout markup
		printf("Build atlas %s...\n", desc.name.c_str());

		std::vector<png_utils::ImageHolder> images;

		AtlasMarkup atlasMarkup(AtlasTextureWidth, AtlasTextureHeight);
		for (const auto& path : desc.imagePaths)
		{
			printf("ADD %s\n", path.c_str());

			images.push_back(png_utils::OpenFile(path.c_str()));
			const auto& backImage = images.back();

			const auto accure = atlasMarkup.accureRect(backImage->width, backImage->height);
			if (!accure)
			{
				printf("Error: failed to accure rect %d/%d\n", (int)backImage->width, (int)backImage->height);
				break;
			}
		}

		// Now really merge them some way
        const auto atlasImage = png_utils::CreateImageByMarkup(images, atlasMarkup.getLayout(), AtlasTextureWidth, AtlasTextureHeight);
		auto savePath = atlasFolderPath;
		savePath += ".png";

		// Save to file
		const auto isSaved = png_utils::SaveToFile(savePath.c_str(), atlasImage);
		if (!isSaved)
		{
			printf("Error: failed to save atlas %s\n", savePath.c_str());
			continue;
		}

		printf("Atlas %s created\n", desc.name.c_str());
	}
}
