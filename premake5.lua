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

	include "Nutcracker/vendor/GLFW"
	include "Nutcracker/vendor/Glad"
	include "Nutcracker/vendor/imgui"

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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"$(ProjectDir)src",
		"%{prj.name}/vendor/spdlog/include",
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
			"NC_PLATFORM_WINDOWS",
			"NC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

		filter "configurations:Debug"
			defines "NC_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "NC_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "NC_DIST"
			buildoptions "/MDd"
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
		"Nutcracker/src",
		"%{IncludeDir.glm}"
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
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "NC_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "NC_DIST"
			buildoptions "/MD"
			optimize "On"



		 
