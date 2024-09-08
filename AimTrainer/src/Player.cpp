#include "Player.h"


Player::Player(Transform transform)
	: m_Transform(std::make_shared<Transform>(transform)),
	m_Gun(m_Transform)
{
}

void Player::OnUpdate(float deltaTime)
{
	m_Gun.OnUpdate(deltaTime);
}

void Player::Shoot(std::map<int, std::optional<PhysicsObject>>& sceneObjects)
{
	m_Gun.Shoot(sceneObjects);
}

std::shared_ptr<Transform> Player::GetSharedTransform()
{
	return m_Transform;
}

