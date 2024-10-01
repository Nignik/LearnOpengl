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

const glm::ivec2 RES = {1024, 1024};
const int amount = RES.x * RES.y;

int main()
{
	NoodleEngine engine;
	NoodleGui gui(engine.GetWindow());

	gui.ShowControllerSettings(engine.GetController());

	g_objectsManager->Init();

	auto hashShader = std::make_shared<Shader>("shaders/hash.vs", "shaders/hash.fs");

	std::vector<int> hashes(amount);
	Material material(hashShader);
	for (int i = 0; i < amount; i++)
	{
		float temp;
		hashes[i] = (int)(std::modf(i * 0.381f, &temp) * 256.0f);
	}
	
	std::vector<glm::mat4> transforms;
	transforms.reserve(amount);
	for (int i = 0; i < RES.x; i++)
	{
		for (int j = 0; j < RES.y; j++)
		{
			Transform t(vec3(1.0f * i, 1.0f, 1.0f * j), 0.0f, 0.0f, 0.0f, vec3(1.0f));
			transforms.push_back(t.GetTransformMatrix());
		}
	}

	auto mesh = Procedural::CubeMesh();
	InstancedMesh iMesh(mesh, material, transforms, hashes, amount);

	while (engine.IsRunning())
	{
		engine.StartFrame();
		int a;

		iMesh.Draw();

		gui.RenderFrame();
		engine.EndFrame();
	}

	g_objectsManager->Shutdown();
}