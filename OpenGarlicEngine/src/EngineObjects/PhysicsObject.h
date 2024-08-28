#pragma once

#include <glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/transform.hpp>
#include <vector>

#include "../Shader.h"
#include "../Mesh.h"
#include "../Transform.h"
#include "../Collider.h"
#include "../Model.h"

using glm::vec3;
using glm::mat4;

class PhysicsObject
{
public:

	template<typename ColliderType>
	PhysicsObject(Model& model, std::shared_ptr<Transform> transform, ColliderType&& collider, unsigned int id, vec3 velocity, float mass)
		: m_Model(model),
		m_Transform(transform),
		m_Collider(collider),
		m_Id(id),
		m_Mass(mass),
		m_Velocity(velocity)
	{
	}

	void Draw(Shader& shader);
	void Move(float deltaTime, std::vector<PhysicsObject>& otherObjects);

	bool IsColliding(PhysicsObject& other);

	Collider GetCollider();
	vec3 GetVelocity();
	void SetVelocity(vec3 newVelocity);
	vec3 GetPosition();
	void SetPosition(vec3 newPosition);
	std::shared_ptr<Transform> GetSharedTransform();
	unsigned int GetId();

private:
	unsigned int m_Id;

	Model m_Model;
	std::shared_ptr<Transform> m_Transform;
	Collider m_Collider;

	vec3 m_Velocity;
	float m_Mass;
};
