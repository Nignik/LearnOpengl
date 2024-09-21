#include "PhysicsObject.h"

#include "ObjectsManager.h"
#include "PhysicsEngine.h"

extern Global::ObjectsManager* g_objectsManager;
extern Global::PhysicsEngine* g_physicsEngine;

PhysicsObject::PhysicsObject(std::shared_ptr<Model> model, std::shared_ptr<Transform> transform, std::shared_ptr <RigidBody> rigidBody)
	: m_id(g_objectsManager->GenerateObjectId()),
	m_model(model),
	m_transform(transform),
	m_rigidBody(std::move(rigidBody))
{
	g_physicsEngine->AddComponent(m_rigidBody);
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

