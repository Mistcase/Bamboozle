require "export-compile-commands"

workspace "Bubble"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Bubble/third-party/GLFW/include"
IncludeDir["Glad"] = "Bubble/third-party/Glad/include"
IncludeDir["ImGui"] = "Bubble/third-party/ImGui"
IncludeDir["glm"] = "Bubble/third-party/glm"

include "Bubble/third-party/GLFW"
include "Bubble/third-party/Glad"
include "Bubble/third-party/ImGui"

project "Bubble"
    location "Bubble"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/" .. outputdir .. "/%{prj.name}")

    pchheader "bubblepch.h"
	pchsource "Bubble/src/bubblepch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/third-party/glm/glm/**.hpp",
         "%{prj.name}/third-party/glm/glm/**.inl"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/third-party/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "BUBBLE_PLATFORM_WINDOWS",
            "BUBBLE_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "BUBBLE_DEBUG"
        symbols "on"

    filter "configurations:Release"
        defines "BUBBLE_RELEASE"
        optimize "on"

    filter "configurations:Dist"
        defines "BUBBLE_DIST"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Bubble/third-party/spdlog/include",
        "Bubble/src",
        "Bubble/third-party",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Bubble"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "BUBBLE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "BUBBLE_DEBUG"
        symbols "on"

    filter "configurations:Release"
        defines "BUBBLE_RELEASE"
        optimize "on"

    filter "configurations:Dist"
        defines "BUBBLE_DIST"
        optimize "on"