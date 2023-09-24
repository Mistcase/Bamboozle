#pragma once

#include <string>
#include <vector>

struct AtlasDesc
{
	std::string name;
	std::vector<std::string> imagePaths;
};

using AtlasDescList = std::vector<AtlasDesc>;
