#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using glm::vec3;

namespace Color
{
	constexpr vec3 RED = vec3(1.0f, 0.0f, 0.0f);
	constexpr vec3 YELLOW = vec3(0.8f, 0.8f, 0.0f);
	constexpr vec3 GREEN = vec3(0.0f, 0.85f, 0.0f);
	constexpr vec3 CYAN = vec3(0.0f, 0.85f, 0.85f);
	constexpr vec3 BLUE = vec3(0.0f, 0.0f, 1.0f);
	constexpr vec3 PINK = vec3(0.8f, 0.0f, 0.5f);
}