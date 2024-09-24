#include <IncludeEngine.h>

#include <glm/gtc/random.hpp>

#include <Utils.h>

extern Global::ObjectsManager* g_objectsManager;
extern Global::PhysicsEngine* g_physicsEngine;

int main()
{
	NoodleEngine engine;

	g_physicsEngine->Init();
	g_objectsManager->Init();

	auto mesh = Procedural::CubeMesh();
	std::shared_ptr<Texture> texture = std::make_shared<Texture>(TextureFromFile("bricks2_disp.jpg", "resources/textures"), "texture_diffuse", "resources/textures");
	mesh->AddTexture(texture);
	auto model = std::make_shared<Model>(mesh);

	auto crateMaterial = std::make_shared<Material>(std::make_shared<Shader>("shaders/crate_shader.vs", "shaders/crate_shader.fs"));

	std::shared_ptr<Transform> sharedTransform = std::make_shared<Transform>(vec3(0.0f), 0.0f, 0.0f, 0.0f, vec3(4.0f));
	std::shared_ptr<RigidBody> rigidBody = std::make_shared<RigidBody>(0.0f, vec3(0.0f), sharedTransform);
	std::shared_ptr<Collider> collider = std::make_shared<Collider>(mesh, sharedTransform);
	rigidBody->AddCollider(collider);
	auto crate = std::make_unique<PhysicsObject>(model, sharedTransform, rigidBody);
	crate->AddMaterial(crateMaterial);

	while (engine.IsRunning())
	{
		engine.StartFrame();

		g_physicsEngine->Update();
		crate->Draw();

		engine.EndFrame();
	}

	g_physicsEngine->Shutdown();
	g_objectsManager->Shutdown();
}