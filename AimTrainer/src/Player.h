#pragma once

#include <IncludeEngine.h>

#include <optional>

#include "Gun.h"

class Player
{
public:
	Player(Transform transform);

	void OnUpdate(float deltaTime);
	void Shoot(std::map<int, std::optional<PhysicsObject>>& sceneObjects);

	std::shared_ptr<Transform> GetSharedTransform();

private:
	std::shared_ptr<Transform> m_Transform;
	Gun m_Gun;
};