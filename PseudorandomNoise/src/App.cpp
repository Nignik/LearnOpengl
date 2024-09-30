#include <IncludeEngine.h>

#include <algorithm>

#include <glm/gtc/random.hpp>

#include <Utils.h>
#include <numeric>

extern Global::ObjectsManager* g_objectsManager;

class HashMaterial : public Material
{
public:
	HashMaterial(std::shared_ptr<Shader> shader)
		: Material(shader)
	{
	}

	void Use() override
	{
		SetShaderParameter("hash", m_hash);
	}

	void SetHash(float hash)
	{
		m_hash = hash;
	}

private:
	float m_hash{};
};

const glm::ivec2 RES = {32, 32};

int main()
{
	NoodleEngine engine;
	NoodleGui gui(engine.GetWindow());

	gui.ShowControllerSettings(engine.GetController());

	g_objectsManager->Init();

	std::vector<int> hashes(RES.x * RES.y);
	for (int i = 0; i < RES.x * RES.y; i++)
	{
		float temp;
		hashes[i] = (int)(std::modf(i * 0.381f, &temp) * 256.0f);
	}
	auto material = std::make_shared<HashMaterial>(std::make_shared<Shader>("shaders/hash.vs", "shaders/hash.fs"));

	auto mesh = Procedural::CubeMesh();
	auto model = std::make_shared<Model>(mesh);
	std::vector<Drawable> cubes;
	cubes.reserve(RES.x * RES.y);
	for (int i = 0; i < RES.x; i++)
	{
		for (int j = 0; j < RES.y; j++)
		{
			cubes.emplace_back(model, std::make_shared<Transform>(vec3(1.0f * i, 1.0f, 1.0f * j), 0.0f, 0.0f, 0.0f, vec3(1.0f)), material);
		}
	}

	while (engine.IsRunning())
	{
		engine.StartFrame();

		for (size_t i = 0; i < cubes.size(); i++)
		{
			material->SetHash((1.0f / 255.0f) * (hashes[i] & 255));
			cubes[i].Draw();
		}

		gui.RenderFrame();
		engine.EndFrame();
	}

	g_objectsManager->Shutdown();
}