#include "PhysicsObject.h"


PhysicsObject::PhysicsObject(Material material, vec3 position, GLuint VBO, GLuint VAO, GLuint EBO, size_t indicesCount, Shader& pShader,
							float mass = 1.0f, vec3 velocity = {0.0f, 0.0f, 0.0f})
	: Drawable(position, pShader, VBO, VAO, EBO, indicesCount),
	m_Material(material),
	m_Mass(mass),
	m_Velocity(velocity)
{
}

void PhysicsObject::Draw(glm::mat4& projection, glm::mat4& view, glm::vec3& cameraPosition, const Light& light)
{
	m_Shader.use();

	m_Shader.setMat4("model", m_Model);
	m_Shader.setMat4("view", view);
	m_Shader.setMat4("projection", projection);
	m_Shader.setVec3("viewPos", cameraPosition);

	m_Shader.setVec3("material.ambient", m_Material.ambient);
	m_Shader.setVec3("material.diffuse", m_Material.diffuse);
	m_Shader.setVec3("material.specular", m_Material.specular);
	m_Shader.setFloat("material.shininess", m_Material.shininess);

	m_Shader.setVec3("light.position", light.position);
	m_Shader.setVec3("light.ambient", light.ambient);
	m_Shader.setVec3("light.diffuse", light.diffuse);
	m_Shader.setVec3("light.specular", light.specular);

	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLES, GLsizei(m_IndicesCount), GL_UNSIGNED_INT, 0);
}


vec3 PhysicsObject::GetVelocity()
{
	return m_Velocity;
}

void PhysicsObject::SetVelocity(vec3 newVelocity)
{
	m_Velocity = newVelocity;
}

vec3 PhysicsObject::GetPosition()
{
	return m_Position;
}

void PhysicsObject::SetPosition(vec3 newPosition)
{
	m_Position = newPosition;
	m_Model = glm::translate(mat4(1.0f), m_Position);
}

