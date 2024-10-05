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
	
	gui.AddSlider(std::make_shared<TypedSlider<float>>("Translation x", [&scene](float position) {
		auto trs = scene.GetDomainTrs();
		auto pos = trs->GetPosition();
		pos.x = position;
		trs->SetPosition(pos);
		scene.GenerateMesh();
		},
		0.0f, 0.0f, 100.0f));
	gui.AddSlider(std::make_shared<TypedSlider<float>>("Translation y", [&scene](float position) {
		auto trs = scene.GetDomainTrs();
		auto pos = trs->GetPosition();
		pos.y = position;
		trs->SetPosition(pos);
		scene.GenerateMesh();
		},
		0.0f, 0.0f, 100.0f));
	gui.AddSlider(std::make_shared<TypedSlider<float>>("Translation z", [&scene](float position) {
		auto trs = scene.GetDomainTrs();
		auto pos = trs->GetPosition();
		pos.z = position;
		trs->SetPosition(pos);
		scene.GenerateMesh();
		},
		0.0f, 0.0f, 100.0f));

	gui.AddSlider(std::make_shared<TypedSlider<float>>("Pitch", [&scene](float rotation) {
			auto trs = scene.GetDomainTrs();
			trs->Rotate({ rotation, 0.0f,  0.0f });
			scene.GenerateMesh();
		},
		0.0f, 0.0f, 90.0f));
	gui.AddSlider(std::make_shared<TypedSlider<float>>("Yaw", [&scene](float rotation) {
		auto trs = scene.GetDomainTrs();
		trs->Rotate({ 0.0f, rotation, 0.0f });
		scene.GenerateMesh();
		}, 0.0f, 0.0f, 90.0f));
	gui.AddSlider(std::make_shared<TypedSlider<float>>("Roll", [&scene](float rotation) {
		auto trs = scene.GetDomainTrs();
		trs->Rotate({ 0.0f, 0.0f, rotation });
		scene.GenerateMesh();
		}, 0.0f, 0.0f, 90.0f));

	gui.AddSlider(std::make_shared<TypedSlider<int>>("Scale x", [&scene](int scale) {
		auto trs = scene.GetDomainTrs();
		auto scl = trs->GetScale();
		scl.x = scale;
		trs->SetScale(scl);
		scene.GenerateMesh();
		},
		1, 1, 128));
	gui.AddSlider(std::make_shared<TypedSlider<int>>("Scale y", [&scene](int scale) {
		auto trs = scene.GetDomainTrs();
		auto scl = trs->GetScale();
		scl.y = scale;
		trs->SetScale(scl);
		scene.GenerateMesh();
		},
		1, 1, 128));
	gui.AddSlider(std::make_shared<TypedSlider<int>>("Scale z", [&scene](int scale) {
		auto trs = scene.GetDomainTrs();
		auto scl = trs->GetScale();
		scl.z = scale;
		trs->SetScale(scl);
		scene.GenerateMesh();
		},
		1, 1, 128));
}