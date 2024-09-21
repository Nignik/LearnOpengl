project "ObjectManagerTest"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    files {
        "src/**.h", "src/**.cpp",
    }

    useEngine()