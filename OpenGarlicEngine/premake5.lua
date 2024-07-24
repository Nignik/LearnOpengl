project "OpenGarlicEngine"
    kind "ConsoleApp"
    targetdir "bin/%{cfg.buildcfg}"
    cppdialect "c++20"

    files { 
        "**.h", "**.cpp",
        "%{wks.location}/external/glad/src/**.c",
    }

    function copyShaders()
        local sourceDir = path.join(os.getcwd(), "shaders")
        local destDir = path.join(targetdir(), "shaders")
        os.mkdir(destDir)
        os.execute('xcopy /s /y "' .. sourceDir .. '" "' .. destDir .. '"')
    end

    -- Pre-build step to copy shaders
    prebuildcommands { copyShaders() }

    includedirs {
        "%{wks.location}/external/glad/include",
        "%{wks.location}/external/glfw/include",
        "%{wks.location}/external/glm",
        "%{wks.location}/external/imgui",
        "%{wks.location}/external/imgui/backends"
    }

    libdirs {
        "%{wks.location}/external/glfw/lib-vc2022",
    }

    links {"glfw3", "opengl32"}


    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        runtime "Debug"
  
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        runtime "Release"