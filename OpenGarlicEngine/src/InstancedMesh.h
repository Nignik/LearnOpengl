#pragma once

#include <glm/glm.hpp>

#include "Mesh.h"
#include "Material.h"

class InstancedMesh
{
public:
	InstancedMesh(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, std::vector<std::shared_ptr<Transform>>& translations);

	void Draw();

private:
	std::shared_ptr<Mesh> m_mesh;
	std::shared_ptr<Material> m_material;

	std::vector<std::shared_ptr<Transform>> m_transforms;
};