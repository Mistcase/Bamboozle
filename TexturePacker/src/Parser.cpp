#include "Parser.h"

Parser::Parser(const char* workingDirectory)
{
	if (std::filesystem::exists(workingDirectory))
	{
		m_atlasesFolderPath = workingDirectory;
	}
	else
	{
		printf("Invalid path\n");
	}
}

AtlasDescList Parser::parse() const
{
	AtlasDescList atlasList;
    for (const auto& entry : std::filesystem::directory_iterator{m_atlasesFolderPath})
	{
		if (!entry.is_directory())
		{
			continue;
		}

		AtlasDesc& back = atlasList.emplace_back();
		back.name = entry.path().filename();

		for (auto& imageEntry : std::filesystem::directory_iterator{entry})
		{
			const auto& path = imageEntry.path();
			if (path.extension() != ".png")
			{
				printf("Found non .png file: %s, just skip it\n", path.c_str());
				continue;
			}

			back.imagePaths.push_back(path.generic_string());
		}
	}

    return atlasList;
}
