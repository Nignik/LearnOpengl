workspace "LearnOpengl"
    configurations {"Debug", "Release"}
    architecture "x86_64"

    filter { "configurations:Debug" }
		symbols "On"

	filter { "configurations:Release" }
		optimize "On"


    targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
    objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")

    include "OpenGarlicEngine"