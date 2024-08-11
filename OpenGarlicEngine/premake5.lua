project "OpenGarlicEngine"
    kind "StaticLib"
    cppdialect "c++20"

    files { 
        "src/**.h", "src/**.cpp",
        "imgui/**.h", "imgui/**.cpp",
        "%{wks.location}/external/glad/src/**.c",
    }

    includedirs {
        "%{wks.location}/external/glad/include",
        "%{wks.location}/external/glfw/include",
        "%{wks.location}/external/glm",
        "%{wks.location}/external/imgui",
        "%{wks.location}/external/imgui/backends"
    }

    prebuildcommands {
        "echo %{wks.location}/OpenGarlicEngine/shaders",
        "echo %{cfg.targetdir}/bin/Debug/shaders",
        "{COPYDIR} %{wks.location}/OpenGarlicEngine/shaders %{cfg.targetdir}/bin/Debug/shaders"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        runtime "Debug"
  
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        runtime "Release"