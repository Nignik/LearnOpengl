#include "PhysicsObject.h"

#include "ObjectsManager.h"
#include "PhysicsEngine.h"

extern Global::ObjectsManager* g_objectsManager;
extern Global::PhysicsEngine* g_physicsEngine;

PhysicsObject::PhysicsObject(std::shared_ptr<Model> model, std::shared_ptr<Transform> transform, std::shared_ptr <RigidBody> rigidBody, const std::shared_ptr<Material> material)
	: m_id(g_objectsManager->GenerateObjectId()),
	m_model(model),
	m_transform(transform),
	m_rigidBody(std::move(rigidBody)),
	m_material(material)
{
	g_physicsEngine->AddComponent(m_rigidBody);
}

void PhysicsObject::Draw()
{
	m_material->Use();
	m_model->Draw(m_material->GetShader());
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

void PhysicsObject::SetMVP(mat4 view, mat4 projection, vec3 cameraPosition)
{
	m_material->SetMVP(m_transform->GetTransformMatrix(), view, projection);
	m_material->SetShaderParameter("viewPos", cameraPosition);
}

std::shared_ptr<Transform> PhysicsObject::GetSharedTransform()
{
	return m_transform;
}

