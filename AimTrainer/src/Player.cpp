#include "Player.h"


Player::Player(Transform transform)
	: m_Transform(std::make_shared<Transform>(transform))
{
}

void Player::Shoot(std::map<int, std::optional<PhysicsObject>>& sceneObjects)
{
	if (m_Shoot)
	{
		Ray ray(m_Transform->GetPosition(), m_Transform->GetForwardDirection());
		std::unique_ptr<PhysicsObject> hit = ray.RayCast(sceneObjects);
		if (hit != nullptr)
		{
			sceneObjects.erase(hit->GetId());
		}

		m_Shoot = false;
	}
}

void Player::SetShoot()
{
	m_Shoot = true;
}

void Player::StopShooting()
{
	m_Shoot = false;
}

std::shared_ptr<Transform> Player::GetSharedTransform()
{
	return m_Transform;
}

