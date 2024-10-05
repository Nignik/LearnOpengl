#include "InstancedMesh.h"

#include <cassert>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

InstancedMesh::InstancedMesh(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, int amount)
	: m_mesh(mesh),
	m_material(material),
	m_amount(amount)
{
}

InstancedMesh::InstancedMesh(InstancedMesh&& other) noexcept
	: m_mesh(std::move(other.m_mesh)),
	m_material(std::move(other.m_material)),
	m_amount(other.m_amount),
	m_ssbos(std::move(other.m_ssbos))
{
	other.m_amount = 0;
}


InstancedMesh& InstancedMesh::operator=(InstancedMesh&& other) noexcept
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

InstancedMesh::~InstancedMesh()
{
	DeleteSsbos();
}

void InstancedMesh::Draw()
{
	auto& frameData = Global::FrameData::GetInstance();

	m_material->Use();

	m_material->SetShaderParameter("view", frameData.view);
	m_material->SetShaderParameter("projection", frameData.projection);
	m_material->SetShaderParameter("viewPos", frameData.position);

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
