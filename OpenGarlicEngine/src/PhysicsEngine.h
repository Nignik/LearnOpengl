#pragma once

#include <vector>
#include <memory>

#include "Component.h"
#include "Collider.h"
#include "RigidBody.h"

namespace Global
{
	class PhysicsEngine
	{
	public:
		PhysicsEngine(const PhysicsEngine&) = delete;
		PhysicsEngine& operator=(const PhysicsEngine&) = delete;

		static void Init();
		static void Shutdown();

		static void Update(float deltaTime);
		static bool CheckCollision(BoundingBox& box, BoundingBox& otherBox);

		static void AddComponent(std::shared_ptr<Component> newComponent);

		static PhysicsEngine& GetInstance();

	private:
		std::vector<std::shared_ptr<Collider>> m_colliders;
		std::vector<std::shared_ptr<RigidBody>> m_rigidBodies;

		PhysicsEngine();
		~PhysicsEngine();
	};
}
