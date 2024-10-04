#include <IncludeEngine.h>

#include <algorithm>
#include <numeric>

#include <glm/gtc/random.hpp>

#include "SmallXXHash.h"

extern Global::ObjectsManager* g_objectsManager;

static std::unique_ptr<InstancedMesh> GenerateInstancedMesh(int res, int seed, float verticalOffset, Material& material) 
{
	float invRes = 1.0f / res;
	int amount = res * res;

	std::vector<SmallXXHash> hashes;
	hashes.reserve(amount);
	for (int i = 0; i < amount; i++)
	{
		uint32_t v = (int)(invRes * i + 0.00001);
		uint32_t u = i - res * v;

		hashes.push_back(SmallXXHash(seed).Eat(u).Eat(v));
	}

	std::vector<glm::mat4> transforms;
	transforms.reserve(amount);
	for (int i = 0; i < res; i++)
	{
		for (int j = 0; j < res; j++)
		{
			float yOffset = ((1.0 / 255.0) * (hashes[i * res + j] >> 24) - 0.5) * verticalOffset;
			Transform t(vec3(1.0f * i, yOffset, 1.0f * j), 0.0f, 0.0f, 0.0f, vec3(1.0f));
			transforms.push_back(t.GetTransformMatrix());
		}
	}

	auto mesh = Procedural::CubeMesh();
	auto iMesh = std::make_unique<InstancedMesh>(mesh, material, amount);
	iMesh->AddSsbo(transforms);

	std::vector<uint32_t> h;
	h.reserve(hashes.size());
	for (auto& hash : hashes)
	{
		h.push_back(hash);
	}
	iMesh->AddSsbo(h);

	return iMesh;
}

int main()
{
	NoodleEngine engine;
	NoodleGui gui(engine.GetWindow());

	gui.ShowControllerSettings(engine.GetController());

	g_objectsManager->Init();

	auto hashShader = std::make_shared<Shader>("shaders/hash.vs", "shaders/hash.fs");
	Material material(hashShader);

	int res = 32;
	int seed = 0;
	float verticalOffset = 0.0f;

	auto iMesh = GenerateInstancedMesh(res, seed, verticalOffset, material);

	gui.AddSlider(std::make_shared<TypedSlider<int>>("Resolution", [&](int newRes) {
		res = newRes;
		iMesh = GenerateInstancedMesh(res, seed, verticalOffset, material);
		}, res, 0, 64));

	gui.AddSlider(std::make_shared<TypedSlider<int>>("Seed", [&](int newSeed) {
		seed = newSeed;
		iMesh = GenerateInstancedMesh(res, seed, verticalOffset, material);
		}, seed, 0, 64));

	gui.AddSlider(std::make_shared<TypedSlider<float>>("Vertical Offset", [&](float newOffset) {
		verticalOffset = newOffset;
		iMesh = GenerateInstancedMesh(res, seed, verticalOffset, material);
		}, verticalOffset, 0.0f, 3.0f));

	while (engine.IsRunning())
	{
		engine.StartFrame();

		iMesh->Draw();

		gui.RenderFrame();
		engine.EndFrame();
	}

	g_objectsManager->Shutdown();
}