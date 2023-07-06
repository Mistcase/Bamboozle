#include "Helpers.h"

#if defined(__APPLE__)
#    include <CoreFoundation/CoreFoundation.h>
#endif

namespace
{
    std::filesystem::path GetResourcePathBase()
    {
#if defined(DEBUG)
        static std::filesystem::path _debugPath;
        if (_debugPath.empty())
        {
            const auto* BBZL_DEV_RES_PATH = std::getenv("BBZL_DEV_RES_PATH");
            if (BBZL_DEV_RES_PATH != nullptr)
            {
                std::string str = BBZL_DEV_RES_PATH;
                str.push_back(std::filesystem::path::preferred_separator);
                
                _debugPath = std::filesystem::path(str);
                return _debugPath;
            }
        }
        else
        {
            return _debugPath;
        }

#endif

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

#include <glm/glm.hpp>
#include <vector>

namespace helpers
{
    std::filesystem::path MakePath(std::string rawPath)
    {
        auto base = GetResourcePathBase();
        auto target = std::filesystem::path(rawPath).make_preferred();

        return base / target;
    }

} // namespace helpers
