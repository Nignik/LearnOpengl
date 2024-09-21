#include "Collider.h"
#include "PhysicsEngine.h"
#include "Objectsmanager.h"

extern Global::PhysicsEngine* g_physicsEngine;
extern Global::ObjectsManager* g_objectsManager;

Collider::Collider(std::shared_ptr<Mesh> mesh, std::weak_ptr<Transform> transform)
	: m_mesh(mesh),
	m_transform(transform)
{
	m_id = g_objectsManager->GenerateObjectId();
}

void Collider::Activate()
{

}

void Collider::OnUpdate(float deltaTime)
{

}

uint32_t Collider::GetId() const
{
	return m_id;
}

BoundingBox Collider::GetBoundingBox() const
{
	if (auto transform = m_transform.lock())
	{
		auto position = transform->GetPosition();
		auto scale = transform->GetScale();
		return BoundingBox{
			.x1 = position.x - scale.x, .x2 = position.x + scale.x,
			.y1 = position.y - scale.y, .y2 = position.y + scale.y,
			.z1 = position.z - scale.z, .z2 = position.z + scale.z,
		};
	}

	std::cerr << "Collider has no parent transform" << std::endl;
	return BoundingBox{};
}

void Collider::SetCollision(bool isColliding)
{
	m_isColliding = isColliding;
}

bool Collider::IsColliding() const
{
	return m_isColliding;
}

std::weak_ptr<Transform> Collider::GetTransform()
{
	return m_transform;
}