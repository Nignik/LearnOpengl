#pragma once

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "../Shader/shader_m.h"
#include "../Shader/ShaderStructs.h"

using glm::mat4;
using glm::vec3;

class Drawable
{
public:
	Drawable(vec3 position, Shader& pShader, GLuint VBO, GLuint VAO, GLuint EBO, size_t indicesCount)
		: m_Position(position),
		m_Shader(pShader),
		m_VBO(VBO),
		m_VAO(VAO),
		m_EBO(EBO),
		m_IndicesCount(indicesCount),
		m_Model(glm::translate(mat4(1.0f), position))
	{
	};

	virtual void Draw(mat4& projection, mat4& view, vec3& cameraPosition, const Light& light) {};

protected:
	GLuint m_VBO, m_VAO, m_EBO;
	size_t m_IndicesCount;

	Shader m_Shader;
	mat4 m_Model;
	vec3 m_Position;
};