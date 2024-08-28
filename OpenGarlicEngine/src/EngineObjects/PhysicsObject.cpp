#include "PhysicsObject.h"


void PhysicsObject::Draw(Shader& shader)
{
	m_Model.Draw(shader);
}


void PhysicsObject::Move(float deltaTime, std::vector<PhysicsObject>& otherObjects)
{
	vec3 prevPosition = m_Transform->GetPosition();
	m_Transform->SetPosition(m_Transform->GetPosition() + m_Velocity * deltaTime);
	for (auto& other : otherObjects)
	{
		if (other.GetId() != m_Id && IsColliding(other))
		{
			m_Transform->SetPosition(prevPosition);
			break;
		}
	}
}

bool PhysicsObject::IsColliding(PhysicsObject& other)
{
	return m_Collider.IsColliding(other.GetCollider());
}

Collider PhysicsObject::GetCollider()
{
	return m_Collider;
}

vec3 PhysicsObject::GetVelocity()
{
	return m_Velocity;
}

void PhysicsObject::SetVelocity(vec3 newVelocity)
{
	m_Velocity = newVelocity;
}

vec3 PhysicsObject::GetPosition()
{
	return m_Transform->GetPosition();
}

void PhysicsObject::SetPosition(vec3 newPosition)
{
	m_Transform->SetPosition(newPosition);
}

std::shared_ptr<Transform> PhysicsObject::GetSharedTransform()
{
	return m_Transform;
}

unsigned int PhysicsObject::GetId()
{
	return m_Id;
}

