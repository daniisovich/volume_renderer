project "glad"
	kind "StaticLib"
	staticruntime "on"

	language "C"

	targetdir (bindir .. "/%{prj.name}")
	objdir (intdir .. "/%{prj.name}")

	files {
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c",
	}

	includedirs {
		"include",
	}
	
	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
