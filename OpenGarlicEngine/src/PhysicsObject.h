#pragma once

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <vector>

#include "Shader.h"
#include "Mesh.h"
#include "Transform.h"
#include "Collider.h"
#include "Model.h"
#include "RigidBody.h"
#include "Material.h"

using glm::vec3;
using glm::mat4;

class PhysicsObject
{
public:
	PhysicsObject(std::shared_ptr<Model> model, std::shared_ptr<Transform> transform, std::shared_ptr <RigidBody> rigidBody);

	void Draw();

	void OnUpdate();

	void AddMaterial(std::shared_ptr<Material> material);

	vec3 GetPosition();
	void SetPosition(vec3 newPosition);

	std::shared_ptr<Transform> GetSharedTransform();

private:
	uint32_t m_id;

	std::shared_ptr<Model> m_model;
	std::shared_ptr<Transform> m_transform;
	std::shared_ptr <RigidBody> m_rigidBody;
	std::shared_ptr<Material> m_material;
};
