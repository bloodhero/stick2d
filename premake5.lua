workspace "stick2d"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "Engine/vendor/glad"
	include "Engine/vendor/imgui"
group ""

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["json"] = "Engine/vendor/json/include"
IncludeDir["entt"]   = "Engine/vendor/entt/single_include"
IncludeDir["Nuklear"]   = "Engine/vendor/Nuklear"
IncludeDir["imgui"]   = "Engine/vendor/imgui"
IncludeDir["glad"]   = "Engine/vendor/glad/include"
IncludeDir["glm"]   = "Engine/vendor/glm"
IncludeDir["stb"]   = "Engine/vendor/stb"
IncludeDir["SDL2"] = "Engine/vendor/SDL2-2.0.12/include"
IncludeDir["ffmpeg"]   = "Engine/vendor/ffmpeg-4.3-win64-dev/include"
IncludeDir["openal"]   = "Engine/vendor/openal-soft-1.20.1-bin/include"
IncludeDir["spdlog"]   = "Engine/vendor/spdlog/include"

LibDir = {}
LibDir["SDL2"]       = "Engine/vendor/SDL2-2.0.12/lib/x64"
LibDir["ffmpeg"]   = "Engine/vendor/ffmpeg-4.3-win64-dev/lib"
LibDir["openal"]   = "Engine/vendor/openal-soft-1.20.1-bin/libs/Win64"

project "Engine"
	location "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Engine/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	-- 宏定义
	defines
	{
	}

	-- 附加包含目录
	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.json}",
		"%{IncludeDir.SDL2}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ffmpeg}",
		"%{IncludeDir.Nuklear}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.openal}",
		"%{IncludeDir.spdlog}"
	}

	-- 附加库目录
	libdirs
	{
		"%{LibDir.SDL2}",
		"%{LibDir.ffmpeg}",
		"%{LibDir.openal}"
	}

	-- 链接的库
	links
	{
		"SDL2.lib",
		"SDL2main.lib",
		"avcodec.lib",
		"avformat.lib",
		"avutil.lib",
		"swscale.lib",
		"OpenAL32.lib",
		"glad",
		"imgui"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "_RELEASE"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Engine/src",
		"%{prj.name}/src",
		"%{IncludeDir.entt}",
		"%{IncludeDir.Nuklear}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.spdlog}"
	}

	links
	{
		"Engine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "_RELEASE"
		runtime "Release"
		optimize "on"
