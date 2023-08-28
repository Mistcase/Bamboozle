#include <cstddef>
#include <fstream>
#include <sstream>

#include "Core.h"

namespace bbzl
{
	namespace helpers
	{
		inline std::string ReadEntireFile(const char* path, size_t* size = nullptr)
		{
			std::ifstream in(path);
			if (!in.is_open())
			{
				return "";
			}

			std::stringstream buffer;
			buffer << in.rdbuf();
			std::string contents(buffer.str());

			return contents;
		}

	} // namespace helpers

} // namespace bbzl
