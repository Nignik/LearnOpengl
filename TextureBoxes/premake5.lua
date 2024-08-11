project "TextureBoxes"
    kind "ConsoleApp"
    cppdialect "c++20"

    files {
        "src/**.h", "src/**.cpp",
        "imgui/**.h", "imgui/**.cpp"
    }

    useEngine()