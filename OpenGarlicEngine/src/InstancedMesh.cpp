#include "InstancedMesh.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

InstancedMesh::InstancedMesh(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, std::vector<std::shared_ptr<Transform>>& transforms)
	: m_mesh(mesh),
	m_material(material),
	m_transforms(transforms)
{

}

void InstancedMesh::Draw()
{
	auto& frameData = Global::FrameData::GetInstance();

	m_material->GetShader()->Use();

	m_material->SetShaderParameter("view", frameData.view);
	m_material->SetShaderParameter("projection", frameData.projection);
	m_material->SetShaderParameter("viewPos", frameData.position);

	for (size_t i = 0; i < 10; i++)
	{
		m_material->SetShaderParameter("transforms[" + std::to_string(i) + "]", m_transforms[i]->GetTransformMatrix());
	}

	glBindVertexArray(m_mesh->GetVAO());
	glDrawElementsInstanced(GL_TRIANGLES, m_mesh->GetIndicesSize(), GL_UNSIGNED_INT, 0, 10);
	glBindVertexArray(0);
}
