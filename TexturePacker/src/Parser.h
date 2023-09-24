#pragma once

#include "AtlasDesc.h"

#include <filesystem>

class Parser
{
public:
	// Takes path to atlases folder
	Parser(const char* workingDirectory);

	bool isReady() const { return !m_atlasesFolderPath.empty(); }

	// Form list of atlases
	AtlasDescList parse() const;

private:
	std::filesystem::path m_atlasesFolderPath;
};
