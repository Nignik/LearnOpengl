#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include <vector>

using glm::vec3;
using glm::mat4;

class Line
{
public:
	Line(std::vector<float>& vertices, vec3 position);

	void Update(vec3 position, vec3 newDirection);

	void Draw(mat4& projection, mat4& view);

private:
	GLuint VBO, VAO;

	Shader shader;
	mat4 model;
};