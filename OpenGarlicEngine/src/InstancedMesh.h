#pragma once

#include <glm/glm.hpp>

#include "Mesh.h"
#include "Material.h"

class InstancedMesh
{
public:
	InstancedMesh(std::shared_ptr<Mesh> mesh, Material material, int amount);
	~InstancedMesh();

	InstancedMesh(const InstancedMesh&) = delete;
	InstancedMesh& operator=(const InstancedMesh&) = delete;

	InstancedMesh(InstancedMesh&& other) noexcept
		: m_mesh(std::move(other.m_mesh)),
		m_material(std::move(other.m_material)),
		m_amount(other.m_amount),
		m_ssbos(std::move(other.m_ssbos))
	{
		other.m_amount = 0;
	}

	InstancedMesh& operator=(InstancedMesh&& other) noexcept
	{
		if (this != &other)
		{
			DeleteSsbos();
			m_mesh = std::move(other.m_mesh);
			m_material = std::move(other.m_material);
			m_amount = other.m_amount;
			m_ssbos = std::move(other.m_ssbos);
			other.m_amount = 0;
		}
		return *this;
	}

	void Draw();

	template<typename T>
	void AddSsbo(std::vector<T>& vec)
	{
		GLuint ssbo;
		glGenBuffers(1, &ssbo);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
		glBufferData(GL_SHADER_STORAGE_BUFFER, vec.size() * sizeof(T), vec.data(), GL_STATIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, (GLuint)m_ssbos.size(), ssbo);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

		m_ssbos.push_back(ssbo);
	}

	void DeleteSsbos();

private:
	std::shared_ptr<Mesh> m_mesh;

	Material m_material;

	int m_amount = 0;

	std::vector<GLuint> m_ssbos;
};