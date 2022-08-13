workspace "DVR"

	architecture "x64"
	startproject "DVR"

	configurations
	{
		"Debug",
		"Release",
	}


outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"
bindir = ("bin/" .. outputdir)
intdir = ("bin-int/" .. outputdir)

group "Dependencies"
	include "DVR/external/glfw"
	include "DVR/external/glad"
group ""


project "DVR"
	
	location "DVR"
	kind "ConsoleApp"

	language "C++"
	cppdialect "C++17"

	
	targetdir (bindir .. "/%{prj.name}")
	objdir (intdir .. "/%{prj.name}")

	pchheader "precompiled/pch.h"
	pchsource "DVR/src/precompiled/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	defines
	{
		"GLFW_INCLUDE_NONE",
	}

	includedirs
	{
		"%{prj.name}/src",
		"DVR/external/glad/include",
		"DVR/external/glfw/include",
		"DVR/external/glm"
	}

	links
	{
		"glfw",
		"glad",
		"opengl32.lib",
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
