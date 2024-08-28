#pragma once

#include <IncludeEngine.h>

#include <optional>

class Player
{
public:
	Player(Transform transform);

	void Shoot(std::map<int, std::optional<PhysicsObject>>& sceneObjects);
	void SetShoot();
	void StopShooting();

	std::shared_ptr<Transform> GetSharedTransform();

private:
	std::shared_ptr<Transform> m_Transform;
	bool m_Shoot = false;
};