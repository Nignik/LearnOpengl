#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;

	Vertex(const glm::vec3& pos, const glm::vec3& norm)
		:
		position(pos),
		normal(norm)
	{
	}
};