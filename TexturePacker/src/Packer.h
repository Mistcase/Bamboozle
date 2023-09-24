#pragma once

#include "AtlasDesc.h"

// TODO: Support different atlas sizes

class Packer
{
public:
	Packer(const AtlasDescList& atlasDescs, const char* outputDirectory);

	void generateAtlases() const;

private:
	const AtlasDescList m_atlasDescs;
	const char* m_outputDirectory;
};
