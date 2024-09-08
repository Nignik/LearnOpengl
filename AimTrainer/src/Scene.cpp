#include "Scene.h"

Scene::Scene()
	: m_Overlay(ShaderOverlay(meshes::generateQuad())),
	m_TargetShader("shaders/BasicVertex.vs", "shaders/BasicFragment.fs"),
	m_Player({ vec3(0.0f), 0.0f, 0.0f, 0.0f, vec3(1.0f) })
{
	m_Overlay.AddShader(Shader("shaders/CrosshairVertex.vs", "shaders/CrosshairFragment.fs"));
}

void Scene::PrepareScene(NoodleEngine& engine)
{
	auto [vertices, indices] = meshes::GenerateCube(vec3(1.0f));
	std::vector<Texture> textures;
	Mesh mesh(vertices, indices, textures);
	Model model(mesh);

	Transform newTransform(vec3(0.0f), 0.0f, 0.0f, 0.0f, vec3(4.0f));
	for (unsigned int i = 0; i < 5; i++)
	{
		auto sharedTransform = std::make_shared<Transform>(newTransform);
		m_Targets[i] = { model, sharedTransform, Collider(mesh, sharedTransform), i, vec3(0.0f), 0.0f };

		newTransform.SetPosition(newTransform.GetPosition() + vec3(30.0f, 0.0f, 0.0f));
	}

	engine.GetController()->AddAction(std::bind([this]() {
		m_Player.Shoot(this->m_Targets);
		}), "shoot");
	engine.GetController()->Possess(m_Player.GetSharedTransform());
}

void Scene::Draw(NoodleEngine& engine)
{
	auto [deltaTime, projection, view, position] = engine.GetFrameData();

	m_Player.OnUpdate(deltaTime);

	Material mat1 = MCooker::EMERALD, mat2 = MCooker::YELLOW_RUBBER;
	Light light(vec3(0.0f), vec3(0.4f), vec3(0.4f), vec3(0.4f));

	m_TargetShader.Use();
	m_TargetShader.SetMat4("projection", projection);
	m_TargetShader.SetMat4("view", view);

	m_TargetShader.SetVec3("material.ambient", mat1.ambient);
	m_TargetShader.SetVec3("material.diffuse", mat1.diffuse);
	m_TargetShader.SetVec3("material.specular", mat1.specular);
	m_TargetShader.SetFloat("material.shininess", mat1.shininess);

	m_TargetShader.SetVec3("light.position", engine.GetCamera()->GetPosition());
	m_TargetShader.SetVec3("light.ambient", light.ambient);
	m_TargetShader.SetVec3("light.diffuse", light.diffuse);
	m_TargetShader.SetVec3("light.specular", light.specular);

	glEnable(GL_DEPTH_TEST);
	for (auto& [id, target] : m_Targets)
	{
		m_TargetShader.SetMat4("model", target->GetSharedTransform()->GetTransformMatrix());
		target->Draw(m_TargetShader);
	}
	glDisable(GL_DEPTH_TEST);

	m_Overlay.Render();
}

