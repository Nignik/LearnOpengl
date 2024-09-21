#include <glm.hpp>

#include <IncludeEngine.h>

#include "ShaderData.h"

using glm::vec3;
using glm::mat4;

int main()
{
	NoodleEngine engine;
	NoodleGui gui(engine.GetWindow());

	auto [vertices, indices] = meshes::GenerateCube(vec3(1.0f));
	std::vector<Texture> textures;
	Mesh mesh(vertices, indices, textures);
	Model model(mesh);
	Collider collider(mesh, mat4(1.0f));

	mat4 m1 = glm::scale(mat4(1.0f), vec3(10.0f));
	mat4 m2 = glm::translate(glm::scale(mat4(1.0f), vec3(8.0f)), vec3(50.0f, 0.0f, 0.0f));
	PhysicsObject objectA(model, m1, collider, 0, vec3(1.0f, 0.0f, 0.0f), 3.0f);
	PhysicsObject objectB(model, m2, collider, 1, vec3(-1.0f, 0.0f, 0.0f), 1.0f);

	Shader mainShader("shaders/basicVertex.vs", "shaders/basicFragment.fs");

	std::vector<PhysicsObject> physicsObjects = { std::move(objectA), std::move(objectB) };

	Material mat1 = materials["Basic1"], mat2 = materials["Basic2"];
	Light light = lights["Basic1"];

	while (engine.IsRunning())
	{
		engine.StartFrame();

		auto [deltaTime, projection, view, position] = engine.GenerateFrameData();
		mainShader.SetMat4("projection", projection);
		mainShader.SetMat4("view", view);

		mainShader.SetVec3("material.ambient", mat1.ambient);
		mainShader.SetVec3("material.diffuse", mat1.diffuse);
		mainShader.SetVec3("material.specular", mat1.specular);
		mainShader.SetFloat("material.shininess", mat1.shininess);

		mainShader.SetVec3("light.position", engine.GetCamera()->Position);
		mainShader.SetVec3("light.ambient", light.ambient);
		mainShader.SetVec3("light.diffuse", light.diffuse);
		mainShader.SetVec3("light.specular", light.specular);

		for (auto& body : physicsObjects)
		{
			body.Move(deltaTime, physicsObjects);
			mainShader.SetMat4("model", body.GetTransform());
			body.Draw(mainShader);
		}

		engine.EndFrame();
	}
}