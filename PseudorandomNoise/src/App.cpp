#include <IncludeEngine.h>

#include <algorithm>

#include <glm/gtc/random.hpp>

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
	
	std::vector<std::shared_ptr<Transform>> transforms;
	transforms.reserve(10);
	for (int i = 0; i < 10; i++)
	{
		transforms.push_back(std::make_shared<Transform>(vec3(2.0f * i, 1.0f, 2.0f * i), 0.0f, 0.0f, 0.0f, vec3(2.0f)));
	}

	auto mesh = Procedural::CubeMesh();
	InstancedMesh iMesh(mesh, material, transforms);

	while (engine.IsRunning())
	{
		engine.StartFrame();

		iMesh.Draw();

		gui.RenderFrame();
		engine.EndFrame();
	}

	g_objectsManager->Shutdown();
}