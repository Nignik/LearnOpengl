#include "RigidBody.h"

#include "PhysicsEngine.h"

extern Global::PhysicsEngine* g_physicsEngine;

RigidBody::RigidBody(float mass, glm::vec3 velocity, std::shared_ptr<Transform> transform)
	: m_mass(mass),
	m_velocity(velocity),
	m_transform(transform),
	m_prevPosition(transform->GetPosition())
{
}

void RigidBody::Activate(float deltaTime)
{
	auto pos = m_transform->GetPosition();
	m_prevPosition = pos;
	m_transform->SetPosition(pos + m_velocity * deltaTime);
}

void RigidBody::OnUpdate()
{
	if (m_collider->IsColliding())
	{
		m_transform->SetPosition(m_prevPosition);
	}
}

void RigidBody::AddCollider(std::shared_ptr<Collider> newCollider)
{
	m_collider = newCollider;
	g_physicsEngine->AddComponent(m_collider);
}

