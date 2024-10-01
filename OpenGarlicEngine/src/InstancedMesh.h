#pragma once

#include <glm/glm.hpp>

#include "Mesh.h"
#include "Material.h"

class InstancedMesh
{
public:
	InstancedMesh(std::shared_ptr<Mesh> mesh, Material material, std::vector<glm::mat4>& transforms, std::vector<int>& hashes, int amount);

	void Draw();

private:
	GLuint m_vbo, m_ssbo;
	std::shared_ptr<Mesh> m_mesh;
	std::vector<glm::mat4> m_transforms;

	Material m_material;

	int m_amount = 0;

	std::vector<int> m_hashes;
	
	void GenerateMesh();
};