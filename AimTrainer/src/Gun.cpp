#include "Gun.h"

Gun::Gun(std::shared_ptr<Transform> transform)
	: m_Transform(transform)
{
}

void Gun::OnUpdate(float deltaTime)
{
	if (!IsReloaded())
	{
		Reload(deltaTime);
	}
	if (IsOnCooldown())
	{
		m_FireCooldown -= deltaTime;
	}
}

void Gun::Shoot(std::map<int, std::optional<PhysicsObject>>& sceneObjects)
{
	if (!IsReloaded() || IsOnCooldown())
		return;

	Ray ray(m_Transform->GetPosition(), m_Transform->GetForwardDirection());
	std::unique_ptr<PhysicsObject> hit = ray.RayCast(sceneObjects);
	if (hit != nullptr)
	{
		sceneObjects.erase(hit->GetId());
	}
	
	m_Ammo--;
	m_FireCooldown = FIRE_RATE;
}

void Gun::Reload(float deltaTime)
{
	m_ReloadTimer -= deltaTime;
	if (m_ReloadTimer <= 0)
	{
		m_ReloadTimer = RELOAD_TIME;
		m_Ammo = MAGAZINE_SIZE;
	}
}

bool Gun::IsReloaded()
{
	return m_Ammo > 0;
}

bool Gun::IsOnCooldown()
{
	return m_FireCooldown > 0;
}

