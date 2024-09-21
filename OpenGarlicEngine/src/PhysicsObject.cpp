#include "PhysicsObject.h"

#include "ObjectsManager.h"

extern Global::ObjectsManager* g_objectsManager;

PhysicsObject::PhysicsObject(std::shared_ptr<Model> model, std::shared_ptr<Transform> transform, std::shared_ptr <RigidBody> rigidBody)
	: m_id(g_objectsManager->GenerateObjectId()),
	m_model(model),
	m_transform(transform),
	m_rigidBody(std::move(rigidBody))
{
	
}

void PhysicsObject::Draw(Shader& shader)
{
	m_model->Draw(shader);
}

void PhysicsObject::OnUpdate()
{
}

vec3 PhysicsObject::GetPosition()
{
	return m_transform->GetPosition();
}

void PhysicsObject::SetPosition(vec3 newPosition)
{
	m_transform->SetPosition(newPosition);
}

std::shared_ptr<Transform> PhysicsObject::GetSharedTransform()
{
	return m_transform;
}

