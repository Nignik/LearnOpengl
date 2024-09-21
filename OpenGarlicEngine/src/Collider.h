#pragma once

#include <glad/glad.h>
#include <glm.hpp>

#include "Mesh.h"
#include "Transform.h"
#include "Component.h"

using glm::vec3;
using glm::mat4;

struct BoundingBox
{
	float x1, x2;
	float y1, y2;
	float z1, z2;
};

class Collider : public Component
{
public:
	Collider(std::shared_ptr<Mesh> mesh, std::weak_ptr<Transform> transform);
	~Collider() override = default;

	void Activate();
	void OnUpdate(float deltaTime);

	uint32_t GetId() const;
	BoundingBox GetBoundingBox() const;

	void SetCollision(bool isColliding);
	bool IsColliding() const;

	std::weak_ptr<Transform> GetTransform();

private:
	uint32_t m_id;
	std::shared_ptr<Mesh> m_mesh;
	std::weak_ptr<Transform> m_transform;

	bool m_isColliding = false;
};