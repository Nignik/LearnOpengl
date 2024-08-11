project "GravitySimulation"
    kind "ConsoleApp"
    cppdialect "c++20"

    files {
        "src/**.h", "src/**.cpp",
        "imgui/**.h", "imgui/**.cpp"
    }

    useEngine()