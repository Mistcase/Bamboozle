#include "Helpers.h"

#if defined (__APPLE__)
#include <CoreFoundation/CoreFoundation.h>
#endif

namespace
{
	std::filesystem::path GetResourcePathBase()
	{
#if defined(__APPLE__)
        CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
        char resourcePath[PATH_MAX];
        if (CFURLGetFileSystemRepresentation(resourceURL, true, (UInt8*)resourcePath, PATH_MAX))
        {
            if (resourceURL != NULL)
            {
				CFRelease(resourceURL);
            }

            std::string base = resourcePath;
            base.push_back(std::filesystem::path::preferred_separator);

            return base;
        }
#endif
		return std::filesystem::path("res/").make_preferred();
	}

} // namespace

namespace helpers
{
	std::filesystem::path MakePath(std::string rawPath)
	{
		auto base = GetResourcePathBase();
        auto target = std::filesystem::path(rawPath).make_preferred();

		return base / target;
	}

} // namespace helpers
