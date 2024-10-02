#include <IncludeEngine.h>

#include <algorithm>
#include <numeric>

#include <glm/gtc/random.hpp>

#include "SmallXXHash.h"

extern Global::ObjectsManager* g_objectsManager;

const glm::ivec2 res = {128, 128};
const int amount = res.x * res.y;

const float invRes = 1.0f / res.x;

int main()
{
	NoodleEngine engine;
	NoodleGui gui(engine.GetWindow());

	gui.ShowControllerSettings(engine.GetController());

	g_objectsManager->Init();

	auto hashShader = std::make_shared<Shader>("shaders/hash.vs", "shaders/hash.fs");

	std::vector<SmallXXHash> hashes(amount);
	Material material(hashShader);
	for (int i = 0; i < amount; i++)
	{
		float temp;
		uint32_t v = (int)(invRes * i + 0.00001);
		uint32_t u = i - res.x * v;
		
		hashes[i].Eat(u);
		hashes[i].Eat(v);
	}
	
	std::vector<glm::mat4> transforms;
	transforms.reserve(amount);
	for (int i = 0; i < res.x; i++)
	{
		for (int j = 0; j < res.y; j++)
		{
			Transform t(vec3(1.0f * i, 1.0f, 1.0f * j), 0.0f, 0.0f, 0.0f, vec3(1.0f));
			transforms.push_back(t.GetTransformMatrix());
		}
	}

	auto mesh = Procedural::CubeMesh();
	InstancedMesh iMesh(mesh, material, amount);
	iMesh.AddSsbo(transforms);

	std::vector<uint32_t> h;
	h.reserve(hashes.size());
	for (auto& hash : hashes)
	{
		h.push_back(hash);
	}
	iMesh.AddSsbo(h);

	while (engine.IsRunning())
	{
		engine.StartFrame();

		iMesh.Draw();

		gui.RenderFrame();
		engine.EndFrame();
	}

	g_objectsManager->Shutdown();
}