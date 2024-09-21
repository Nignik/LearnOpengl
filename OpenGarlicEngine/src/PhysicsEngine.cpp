#include "PhysicsEngine.h"

namespace Global
{
	static PhysicsEngine* g_physicsEngine;

	PhysicsEngine::PhysicsEngine()
	{
	}


	PhysicsEngine::~PhysicsEngine()
	{
	}

	void PhysicsEngine::Init()
	{
		g_physicsEngine = new PhysicsEngine();
	}

	void PhysicsEngine::Shutdown()
	{
		delete g_physicsEngine;
		g_physicsEngine = nullptr;
	}

	void PhysicsEngine::Update(float deltaTime)
	{
		for (auto& body : g_physicsEngine->m_rigidBodies)
		{
			body->Activate(deltaTime);
		}

		for (auto& collider : g_physicsEngine->m_colliders)
		{
			for (auto& otherCollider : g_physicsEngine->m_colliders)
			{
				if (collider->GetId() == otherCollider->GetId())
				{
					continue;
				}

				auto box = collider->GetBoundingBox();
				auto otherBox = otherCollider->GetBoundingBox();

				if (CheckCollision(box, otherBox))
				{
					collider->SetCollision(true);
				}
			}
		}

		for (auto& body : g_physicsEngine->m_rigidBodies)
		{
			body->OnUpdate();
		}
	}

	bool PhysicsEngine::CheckCollision(BoundingBox& box, BoundingBox& otherBox)
	{
		return {
			box.x1 <= otherBox.x2 &&
			box.x2 >= otherBox.x1 &&
			box.y1 <= otherBox.y2 &&
			box.y2 >= otherBox.y1 &&
			box.z1 <= otherBox.z2 &&
			box.z2 >= otherBox.z1
		};
	}

	void PhysicsEngine::AddComponent(std::shared_ptr<Component> newComponent)
	{
		if (auto comp = std::dynamic_pointer_cast<Collider>(newComponent))
		{
			g_physicsEngine->m_colliders.push_back(comp);
		}
		else if (auto comp = std::dynamic_pointer_cast<RigidBody>(newComponent))
		{
			g_physicsEngine->m_rigidBodies.push_back(comp);
		}
	}

	PhysicsEngine& PhysicsEngine::GetInstance()
	{
		return *g_physicsEngine;
	}

}


