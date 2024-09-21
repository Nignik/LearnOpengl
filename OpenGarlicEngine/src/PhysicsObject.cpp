#include "PhysicsObject.h"

#include "ObjectsManager.h"
#include "PhysicsEngine.h"

#include "FrameData.h"

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
	auto& frameData = Global::FrameData::GetInstance();
	m_material->SetMVP(m_transform->GetTransformMatrix(), frameData.view, frameData.projection);
	m_material->SetShaderParameter("viewPos", frameData.position);
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

std::shared_ptr<Transform> PhysicsObject::GetSharedTransform()
{
	return m_transform;
}

