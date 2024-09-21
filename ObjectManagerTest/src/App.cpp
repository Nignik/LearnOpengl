#include <IncludeEngine.h>

#include <random>
#include <vector>

#include <gtc/random.hpp>

extern Global::PhysicsEngine* g_physicsEngine;
extern Global::ObjectsManager* g_objectsManager;

int main()
{
	NoodleEngine engine;

	g_physicsEngine->Init();
	g_objectsManager->Init();

	auto mesh = Procedural::SphereMesh(2.0f);
	auto model = std::make_shared<Model>(mesh);

	std::vector<std::unique_ptr<PhysicsObject>> simulationObjects;
	for (int i = 0; i < 100; i++)
	{
		std::shared_ptr<Transform> sharedTransform = std::make_shared<Transform>(glm::ballRand(100.0f), 0.0f, 0.0f, 0.0f, vec3(4.0f));
		std::shared_ptr<RigidBody> rigidBody = std::make_shared<RigidBody>(0.0f, glm::ballRand(5.0f), sharedTransform);
		std::shared_ptr<Collider> collider = std::make_shared<Collider>(mesh, sharedTransform);
		rigidBody->AddCollider(collider);
		auto cube = std::make_unique<PhysicsObject>(model, sharedTransform, rigidBody);
		simulationObjects.push_back(std::move(cube));
	}

	Shader mainShader("shaders/BasicVertex.vs", "shaders/BasicFragment.fs");

	while (engine.IsRunning())
	{
		engine.StartFrame();

		auto [deltaTime, projection, view, cameraPosition] = engine.GetFrameData();

		g_physicsEngine->Update(deltaTime);
		
		for (auto& cube : simulationObjects)
		{
			SetupBasicShader(mainShader, engine, cube->GetSharedTransform()->GetTransformMatrix());
			cube->Draw(mainShader);
		}

		engine.EndFrame();
	}

	g_physicsEngine->Shutdown();
	g_objectsManager->Shutdown();
}