#pragma once

#include <glm.hpp>
#include <map>
#include <optional>

#include "Collider.h"
#include "EngineObjects/PhysicsObject.h"

using glm::vec3;

class Ray
{
public:
	Ray(vec3 origin, vec3 direction);
	std::unique_ptr<PhysicsObject> RayCast(std::map<int, std::optional<PhysicsObject>>& sceneObjects);

private:
	vec3 m_Origin;
	vec3 m_Direction;

	
};