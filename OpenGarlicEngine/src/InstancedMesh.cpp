#include "InstancedMesh.h"

#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

InstancedMesh::InstancedMesh(std::shared_ptr<Mesh> mesh, Material material, int amount)
	: m_mesh(mesh),
	m_material(material),
	m_amount(amount)
{
}

InstancedMesh::~InstancedMesh()
{
	DeleteSsbos();
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

void InstancedMesh::DeleteSsbos()
{
	if (!m_ssbos.empty())
	{
		glDeleteBuffers(static_cast<GLsizei>(m_ssbos.size()), m_ssbos.data());
		m_ssbos.clear();
	}
}
