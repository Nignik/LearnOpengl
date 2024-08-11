#pragma once

#include <glad/glad.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "../Shader/shader_m.h"
#include <vector>

class Line
{
public:
	Line(std::vector<float>& vertices, glm::vec3 position);

	void Update(glm::vec3 position, glm::vec3 newDirection);

	void Draw(glm::mat4& projection, glm::mat4& view);

private:
	GLuint VBO, VAO;

	Shader shader;
	glm::mat4 model;
};