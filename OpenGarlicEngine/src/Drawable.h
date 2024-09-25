#pragma once

#include <cstdint>
#include <memory>

#include "Model.h"
#include "Material.h"

class Drawable
{
public:
	Drawable(std::shared_ptr<Model> model, std::shared_ptr<Transform> transform, std::shared_ptr<Material> material);

	void Draw();

private:
	uint32_t m_id;

	std::shared_ptr<Model> m_model;
	std::shared_ptr<Transform> m_transform;
	std::shared_ptr<Material> m_material;
};