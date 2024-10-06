#include <IncludeEngine.h>

#include <algorithm>
#include <numeric>

#include <glm/gtc/random.hpp>

#include "Scene.h"

extern Global::ObjectsManager* g_objectsManager;

void initializeGui(NoodleGui& gui, Scene& scene);

int main()
{
	NoodleEngine engine;
	NoodleGui gui(engine.GetWindow());

	gui.ShowControllerSettings(engine.GetController());

	g_objectsManager->Init();

	Scene scene;
	initializeGui(gui, scene);

	while (engine.IsRunning())
	{
		engine.StartFrame();

		scene.Render();

		gui.RenderFrame();
		engine.EndFrame();
	}

	g_objectsManager->Shutdown();
}

void initializeGui(NoodleGui& gui, Scene& scene)
{
	gui.AddSlider(std::make_shared<TypedSlider<int>>("Resolution", std::bind(&Scene::SetRes, &scene, std::placeholders::_1), scene.GetRes(), 0, 64));
	gui.AddSlider(std::make_shared<TypedSlider<int>>("Seed", std::bind(&Scene::SetSeed, &scene, std::placeholders::_1), scene.GetSeed(), 0, 64));
	gui.AddSlider(std::make_shared<TypedSlider<float>>("Vertical Offset", std::bind(&Scene::SetVerticalOffset, &scene, std::placeholders::_1), scene.GetVerticalOffset(), 0.0f, 3.0f));
	gui.AddSlider(std::make_shared<TypedSlider<glm::vec3>>("Translation", std::bind(&Scene::SetDomainPosition, &scene, std::placeholders::_1), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(64.0f)));
	gui.AddSlider(std::make_shared<TypedSlider<glm::vec3>>("Rotation", std::bind(&Scene::SetDomainPosition, &scene, std::placeholders::_1), glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(90.0f)));
	gui.AddSlider(std::make_shared<TypedSlider<glm::ivec3>>("Scale", std::bind(&Scene::SetDomainScale, &scene, std::placeholders::_1), glm::ivec3(1), glm::ivec3(1), glm::ivec3(128)));
}