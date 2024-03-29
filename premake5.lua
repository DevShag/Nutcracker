  workspace "Nutcracker"
    architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}


	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	--Include directories relative to root folder (solution directory)
	IncludeDir={}
	IncludeDir["GLFW"]="Nutcracker/vendor/GLFW/include"
	IncludeDir["Glad"]="Nutcracker/vendor/Glad/include"
	IncludeDir["ImGui"]="Nutcracker/vendor/imgui"
	IncludeDir["glm"]="Nutcracker/vendor/glm"
	IncludeDir["stb_image"]="Nutcracker/vendor/stb_image"

	include "Nutcracker/vendor/GLFW"
	include "Nutcracker/vendor/Glad"
	include "Nutcracker/vendor/imgui"

project "Nutcracker"
     location "Nutcracker"
	 kind "StaticLib"
	 language "C++"
	 cppdialect "C++17"
	 staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ncpch.h"
	pchsource "Nutcracker/src/ncpch.cpp"

	files
	{
	    "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"$(ProjectDir)src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"NC_PLATFORM_WINDOWS",
			"NC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		

		filter "configurations:Debug"
			defines "NC_DEBUG"
			symbols "on"

		filter "configurations:Release"
			defines "NC_RELEASE"
			optimize "on"

		filter "configurations:Dist"
			defines "NC_DIST"
			optimize "on"


project "Sandbox"
     location "Sandbox"
	 kind "ConsoleApp"
	 language "C++"
	 cppdialect "C++17"
	 staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
	    "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Nutcracker/vendor/spdlog/include",
		"Nutcracker/src",
		"Nutcracker/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Nutcracker"
	}

	filter "system:windows"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"NC_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
			defines "NC_DEBUG"
			symbols "on"

		filter "configurations:Release"
			defines "NC_RELEASE"
			optimize "on"

		filter "configurations:Dist"
			defines "NC_DIST"
			optimize "on"



		 
