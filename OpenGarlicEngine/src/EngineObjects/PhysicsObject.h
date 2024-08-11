#pragma once

#include <glm.hpp>
#include <vector>

#include "Drawable.h"
#include "../Shader/ShaderStructs.h"
#include "../Shader/shader_m.h"
#include "../Vertex.h"

using glm::vec3;
using glm::mat4;

class PhysicsObject : public Drawable
{
public:
	PhysicsObject(Material material, vec3 position, GLuint VBO, GLuint VAO, GLuint EBO, size_t indicesCount, Shader& shader, float mass, vec3 velocity);

	void Draw(mat4& projection, mat4& view, vec3& cameraPosition,const Light& light) override;

	vec3 GetVelocity();
	void SetVelocity(vec3 newVelocity);
	vec3 GetPosition();
	void SetPosition(vec3 newPosition);

private:
	Material m_Material;

	vec3 m_Velocity;
	float m_Mass;
};
