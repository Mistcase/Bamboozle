#include <cstddef>

#include "Core.h"

namespace bbzl
{
	namespace helpers
	{
		inline char* ReadEntireFile(const char* path, size_t* size = nullptr)
		{
			auto* stream = fopen(path, "r");
			if (!stream)
			{
				return nullptr;
			}

			fseek(stream, 0, SEEK_END);
			auto _size = ftell(stream);
			fseek(stream, 0, SEEK_SET);

			auto* data = new char[_size];

			fread(data, 1, _size, stream);
			fclose(stream);
            
            if (size != nullptr)
            {
                *size = _size;
            }

			return data;
		}

	} // namespace helpers

} // namespace bbzl
