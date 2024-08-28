#include "Ray.h"


Ray::Ray(vec3 origin, vec3 direction)
	: m_Origin(origin),
	m_Direction(direction)
{
}

std::unique_ptr<PhysicsObject> Ray::RayCast(std::map<int, std::optional<PhysicsObject>>& sceneObjects)
{
	float minimumDistance = 1000000.0f;
	std::unique_ptr<PhysicsObject> objectHit = nullptr;

	for (auto& [id, sceneObject] : sceneObjects)
	{
		vec3 objectDirection = sceneObject->GetPosition() - m_Origin;

		float dotProduct = dot(objectDirection, m_Direction);
		if (dotProduct < 0)
			continue;

		float distance = glm::dot(objectDirection, objectDirection) - dotProduct * dotProduct;
		vec3 radiusVec = sceneObject->GetSharedTransform()->GetScale();
		float radius2 = glm::dot(radiusVec, radiusVec);

		if (distance > radius2)
			continue;

		float d = glm::length(objectDirection);
		if (minimumDistance > d)
		{
			minimumDistance = d;
			objectHit = std::make_unique<PhysicsObject>(*sceneObject);
		}
	}

	return objectHit;
}

