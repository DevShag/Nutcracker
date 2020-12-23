  workspace "Nutcracker"
    architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}


	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Nutcracker"
     location "Nutcracker"
	 kind "sharedLib"
	 language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ncpch.h"
	pchsource "Nutcracker/src/ncpch.cpp"

	files
	{
	    "%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"$(ProjectDir)src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"NC_PLATFORM_WINDOWS",
			"NC_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "NC_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "NC_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "NC_DIST"
			optimize "On"


project "Sandbox"
     location "Sandbox"
	 kind "ConsoleApp"
	 language "C++"

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
		"Nutcracker/src"
	}

	links
	{
		"Nutcracker"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"NC_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
			defines "NC_DEBUG"
			symbols "On"

		filter "configurations:Release"
			defines "NC_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "NC_DIST"
			optimize "On"



		 
