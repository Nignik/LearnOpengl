#pragma once

#include <glm/glm.hpp>

#include "Mesh.h"
#include "Material.h"

class InstancedMesh
{
public:
	InstancedMesh(std::shared_ptr<Mesh> mesh, Material material, int amount);

	void Draw();

	template<typename T>
	void AddSsbo(std::vector<T> vec)
	{
		GLuint ssbo;
		glGenBuffers(1, &ssbo);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
		glBufferData(GL_SHADER_STORAGE_BUFFER, vec.size() * sizeof(T), vec.data(), GL_STATIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, (GLuint)m_ssbos.size(), ssbo);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, (GLuint)m_ssbos.size());

		m_ssbos.push_back(ssbo);
	}

private:
	std::shared_ptr<Mesh> m_mesh;

	Material m_material;

	int m_amount = 0;

	std::vector<GLuint> m_ssbos;
};