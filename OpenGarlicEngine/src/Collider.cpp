#include "Collider.h"


Collider::Collider(Mesh& mesh, std::weak_ptr<Transform> transform)
	: m_Mesh(mesh),
	m_Transform(transform)
{
}

bool Collider::IsColliding(Collider&& other)
{
	auto thisLock = m_Transform.lock();
	auto otherTransform = other.GetTransform();
	auto otherLock = otherTransform.lock();

	if (thisLock && otherLock)
	{
		vec3 thisPos = thisLock->GetPosition();
		vec3 thisScale = thisLock->GetScale();

		vec3 otherPos = otherLock->GetPosition();
		vec3 otherScale = otherLock->GetScale();
		return (
			thisPos.x - thisScale.x <= otherPos.x + otherScale.x &&
			thisPos.x + thisScale.x >= otherPos.x - otherScale.x &&
			thisPos.y - thisScale.y <= otherPos.y + otherScale.y &&
			thisPos.y + thisScale.y >= otherPos.y - otherScale.y &&
			thisPos.z - thisScale.z <= otherPos.z + otherScale.z &&
			thisPos.z + thisScale.z >= otherPos.z - otherScale.z
		);
	}

	std::cerr << "Transform doesn't exist" << std::endl;

	return false;
}

std::weak_ptr<Transform> Collider::GetTransform()
{
	return m_Transform;
}