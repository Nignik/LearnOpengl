#pragma once

#include <map>
#include <optional>

#include <IncludeEngine.h>

#include "Player.h"

class Scene
{
public:
	Scene();

	void PrepareScene(NoodleEngine& engine);
	void Draw(NoodleEngine& engine);

private:
	ShaderOverlay m_Overlay;
	Shader m_TargetShader;
	Player m_Player;
	std::map<int, std::optional<PhysicsObject>> m_Targets;
};