#include <glm.hpp>

#include <IncludeEngine.h>

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

	Shader boxShader("shaders/BasicVertex.vs", "shaders/BasicFragment.fs");

	PhysicsObject box1(model, m1, collider, 0, vec3(1.0f, 0.0f, 0.0f), 3.0f);
	PhysicsObject box2(model, m2, collider, 1, vec3(-1.0f, 0.0f, 0.0f), 1.0f);

	std::vector<PhysicsObject> boxes = { std::move(box1), std::move(box2) };

	Material mat1 = MCooker::EMERALD, mat2 = MCooker::YELLOW_RUBBER;
	Light light(vec3(0.0f), vec3(0.4f), vec3(0.4f), vec3(0.4f));

	//Controller controller(engine.GetCamera()->GetSharedTransform());

	while (engine.IsRunning())
	{
		engine.StartFrame();

		auto [deltaTime, projection, view, position] = engine.GenerateFrameData();
		boxShader.SetMat4("projection", projection);
		boxShader.SetMat4("view", view);

		boxShader.SetVec3("material.ambient", mat1.ambient);
		boxShader.SetVec3("material.diffuse", mat1.diffuse);
		boxShader.SetVec3("material.specular", mat1.specular);
		boxShader.SetFloat("material.shininess", mat1.shininess);

		boxShader.SetVec3("light.position", engine.GetCamera()->GetPosition());
		boxShader.SetVec3("light.ambient", light.ambient);
		boxShader.SetVec3("light.diffuse", light.diffuse);
		boxShader.SetVec3("light.specular", light.specular);

		for (auto& box : boxes)
		{
			boxShader.SetMat4("model", box.GetTransform());
			box.Draw(boxShader);
		}

		engine.EndFrame();
	}
}