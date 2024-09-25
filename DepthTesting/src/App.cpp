#include <IncludeEngine.h>

#include <glm/gtc/random.hpp>

#include <Utils.h>

extern Global::ObjectsManager* g_objectsManager;

int main()
{
	NoodleEngine engine;
	NoodleGui gui(engine.GetWindow());

	gui.ShowControllerSettings(engine.GetController());

	g_objectsManager->Init();

	auto material = std::make_shared<Material>(std::make_shared<Shader>("shaders/crate_shader.vs", "shaders/crate_shader.fs"));

	auto crateMesh = Procedural::CubeMesh();
	auto crateTexture = std::make_shared<Texture>(TextureFromFile("bricks2_disp.jpg", "resources/textures"), "texture_diffuse", "resources/textures");
	crateMesh->AddTexture(crateTexture);
	auto crateModel = std::make_shared<Model>(crateMesh);

	auto floorMesh = Procedural::PlaneMesh();
	auto floorTexture = std::make_shared<Texture>(TextureFromFile("marble.jpg", "resources/textures"), "texture_diffuse", "resources/textures");
	floorMesh->AddTexture(floorTexture);
	auto floorModel = std::make_shared<Model>(floorMesh);

	std::vector<std::unique_ptr<Drawable>> crates;
	for (int i = 0; i < 10; i++)
	{
		crates.push_back(std::make_unique<Drawable>(crateModel, std::make_shared<Transform>(vec3(2.0f * i, 1.0f, 2.0f * i), 0.0f, 0.0f, 0.0f, vec3(2.0f)), material));
	}
	Drawable floor(floorModel, std::make_shared<Transform>(vec3(0.0f), 0.0f, 0.0f, 0.0f, vec3(50.0f)), material);

	while (engine.IsRunning())
	{
		engine.StartFrame();

		for (auto& crate : crates)
		{
			crate->Draw();
		}

		floor.Draw();

		gui.RenderFrame();
		engine.EndFrame();
	}

	g_objectsManager->Shutdown();
}