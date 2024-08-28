#pragma once

#include <glad/glad.h>
#include <glm.hpp>

#include <string>
#include <vector>

#include "Shader.h"

constexpr int MAX_BONE_INFLUENCE = 4;

using glm::vec2, glm::vec3;

struct Vertex
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
	vec3 Tangent;
	vec3 Bitangent;
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture
{
	GLuint id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	template <typename T>
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, T&& textures)
		: m_Vertices(vertices),
		m_Indices(indices),
		m_Textures(std::forward<T>(textures))
	{
		GenerateMesh();
	}

	void Draw(Shader& shader);

private:
	GLuint m_VAO, m_VBO, m_EBO;
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<Texture> m_Textures;

	void GenerateMesh();
};
