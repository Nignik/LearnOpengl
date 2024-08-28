#pragma once

#include <glad/glad.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Transform.h"

using glm::vec3;
using glm::mat4;

class Collider
{
public:
	Collider(Mesh& mesh, std::weak_ptr<Transform> transform);

	bool IsColliding(Collider&& other);

	std::weak_ptr<Transform> GetTransform();

private:
	Mesh m_Mesh;
	std::weak_ptr<Transform> m_Transform;
};