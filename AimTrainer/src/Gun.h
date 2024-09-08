#pragma once

#include <IncludeEngine.h>

constexpr float FIRE_RATE = 0.1f;
constexpr float RELOAD_TIME = 2.0f;
constexpr unsigned int MAGAZINE_SIZE = 10;

class Gun
{
public:
	Gun(std::shared_ptr<Transform> transform);

	void OnUpdate(float deltaTime);
	void Shoot(std::map<int, std::optional<PhysicsObject>>& sceneObjects);
	void Reload(float deltaTime);

	bool IsReloaded();
	bool IsOnCooldown();


private:
	std::shared_ptr<Transform> m_Transform;
	float m_FireCooldown = 0.0f;
	float m_ReloadTimer = RELOAD_TIME;
	unsigned int m_Ammo = MAGAZINE_SIZE;
};