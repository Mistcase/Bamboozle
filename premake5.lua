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

include "Bubble/third-party/GLFW"
include "Bubble/third-party/Glad"
include "Bubble/third-party/ImGui"

project "Bubble"
    location "Bubble"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin/" .. outputdir .. "/%{prj.name}")

    pchheader "bubblepch.h"
	pchsource "Bubble/src/bubblepch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/third-party/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
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

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "BUBBLE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "BUBBLE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "BUBBLE_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"

    language "C++"

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
        "Bubble/src"
    }

    links
    {
        "Bubble"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "BUBBLE_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "BUBBLE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "BUBBLE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "BUBBLE_DIST"
        optimize "On"