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
        "%{wks.location}/external/imgui/backends",
        "%{wks.location}/external/assimp/include"
    }

    libdirs {
        "%{wks.location}/external/glfw/lib-vc2022",
        "%{wks.location}/external/assimp/lib/x64"
    }

    links {"glfw3", "opengl32", "assimp-vc143-mt"}

    --prebuildcommands {
    --    "{COPYDIR} %{wks.location}/OpenGarlicEngine/shaders %{cfg.targetdir}/bin/Debug/shaders",
    --    "{COPYDIR} %{wks.location}/external/assimp/bin/x64 %{cfg.targetdir}/bin/Debug"
    --}