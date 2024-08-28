#pragma once

#include <glad/glad.h>

#include <vector>

#include "../Mesh.h"
#include "../Shader.h"

class TextureBox
{
public:
	TextureBox(std::vector<float>& vertices, std::vector<int> indices, GLuint textureId, Shader& shader);
	~TextureBox();

	void Draw();

private:
	GLuint m_VAO, m_VBO, m_EBO;

	std::vector<float> m_Vertices;
	std::vector<int> m_Indices;
	GLuint m_TextureId;
	Shader m_Shader;

};