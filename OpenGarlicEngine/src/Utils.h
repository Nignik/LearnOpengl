#pragma once

#include "NoodleEngine.h"
#include "Shader.h"
#include "MaterialCooker.h"

inline void SetupBasicShader(Shader& shader, NoodleEngine& engine, glm::mat4 transformMatrix)
{
	auto [deltaTime, projection, view, position] = engine.GetFrameData();

	Material mat1 = MCooker::EMERALD, mat2 = MCooker::YELLOW_RUBBER;
	Light light(vec3(0.0f), vec3(0.4f), vec3(0.4f), vec3(0.4f));

	shader.Use();

	shader.SetVec3("material.ambient", mat1.ambient);
	shader.SetVec3("material.diffuse", mat1.diffuse);
	shader.SetVec3("material.specular", mat1.specular);
	shader.SetFloat("material.shininess", mat1.shininess);

	shader.SetVec3("light.position", engine.GetCamera()->GetPosition());
	shader.SetVec3("light.ambient", light.ambient);
	shader.SetVec3("light.diffuse", light.diffuse);
	shader.SetVec3("light.specular", light.specular);

	shader.SetMat4("projection", projection);
	shader.SetMat4("view", view);
	shader.SetMat4("model", transformMatrix);
}