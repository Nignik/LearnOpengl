workspace "LearnOpengl"
  configurations {"Debug", "Release"}
  architecture "x86_64"

  filter { "configurations:Debug" }
  symbols "On"

  filter { "configurations:Release" }
    optimize "On"

  targetdir ("Build/Bin/%{prj.name}/%{cfg.longname}")
  objdir ("Build/Obj/%{prj.name}/%{cfg.longname}")

  function useEngine()
    includedirs {
      "%{wks.location}/OpenGarlicEngine/src",
      "imgui/**.h", "imgui/**.cpp",
      "%{wks.location}/external/glad/src/**.c",
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
    links {"OpenGarlicEngine", "glfw3", "opengl32", "assimp-vc143-mt"}
  end

  function copyAssimp()
    postbuildcommands {
      "{COPY} " .. "%{wks.location}/external/assimp/bin/x64/assimp-vc143-mt.dll" .. " %{cfg.targetdir}"
    }
  end
  
  include "OpenGarlicEngine"
  --include "GravitySimulation"
  --include "TextureBoxes"  
  --include "CoordinateSystemsTest"
  include "ModelLoadingTest"
  include "AABB"
  include "HorrorGura"
  include "ControllerTest"
  include "AimTrainer"