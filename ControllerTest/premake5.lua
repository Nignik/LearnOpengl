project "ControllerTest"
    kind "ConsoleApp"
    cppdialect "c++20"

    files {
        "src/**.h", "src/**.cpp",
    }

    copyAssimp();

    useEngine()