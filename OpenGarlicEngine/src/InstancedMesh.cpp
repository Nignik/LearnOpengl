#include "InstancedMesh.h"

#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

InstancedMesh::InstancedMesh(std::shared_ptr<Mesh> mesh, Material material, std::vector<glm::mat4>& transforms, std::vector<int>& hashes, int amount)
	: m_mesh(mesh),
	m_material(material),
	m_transforms(transforms),
	m_amount(amount),
	m_hashes(hashes)
{
	assert(m_transforms.size() == m_amount);
	GenerateMesh();
}

void InstancedMesh::Draw()
{
	auto& frameData = Global::FrameData::GetInstance();

	m_material.GetShader()->Use();

	m_material.SetShaderParameter("view", frameData.view);
	m_material.SetShaderParameter("projection", frameData.projection);
	m_material.SetShaderParameter("viewPos", frameData.position);
	
	m_material.Use();

	glBindVertexArray(m_mesh->GetVAO());
	glDrawElementsInstanced(GL_TRIANGLES, m_mesh->GetIndicesSize(), GL_UNSIGNED_INT, 0, m_amount);
	glBindVertexArray(0);
}

void InstancedMesh::GenerateMesh()
{
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_amount * sizeof(glm::mat4), &m_transforms[0], GL_STATIC_DRAW);

	glBindVertexArray(m_mesh->GetVAO());

	std::size_t v4s = sizeof(glm::vec4);
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 4 * v4s, (void*)0);
	glEnableVertexAttribArray(8);
	glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, 4 * v4s, (void*)(1 * v4s));
	glEnableVertexAttribArray(9);
	glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, 4 * v4s, (void*)(2 * v4s));
	glEnableVertexAttribArray(10);
	glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, 4 * v4s, (void*)(3 * v4s));

	glVertexAttribDivisor(7, 1);
	glVertexAttribDivisor(8, 1);
	glVertexAttribDivisor(9, 1);
	glVertexAttribDivisor(10, 1);

	glBindVertexArray(0);

	glGenBuffers(1, &m_ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, m_amount * sizeof(uint32_t), m_hashes.data(), GL_STATIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
