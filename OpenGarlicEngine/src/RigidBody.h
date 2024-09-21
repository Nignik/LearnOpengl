#pragma once

#include <glm.hpp>

#include <memory>

#include "Component.h"
#include "Collider.h"
#include "Transform.h"

class RigidBody : public Component
{
public:
	RigidBody(float mass, glm::vec3 velocity, std::shared_ptr<Transform> transform);

	void Activate(float deltaTime);
	void OnUpdate();

	void xd() override;

	void AddCollider(std::shared_ptr<Collider> newCollider);

private:
	float m_mass;
	glm::vec3 m_velocity;

	std::shared_ptr<Transform> m_transform;
	std::shared_ptr<Collider> m_collider;

	glm::vec3 m_prevPosition;
};