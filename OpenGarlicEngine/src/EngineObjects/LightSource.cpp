#include "LightSource.h"

LightSource::LightSource(vec3 position, Shader& pShader, GLuint VBO, GLuint VAO, GLuint EBO, size_t indicesCount, Light lightParams, float brightness)
	: Drawable(position, pShader, VBO, VAO, EBO, indicesCount),
	m_LightParams(lightParams),
	m_Brightness(brightness)
{
}

void LightSource::Draw(mat4& projection, mat4& view, vec3& cameraPosition, const Light& light)
{
	m_Shader.use();

	m_Shader.setMat4("model", m_Model);
	m_Shader.setMat4("view", view);
	m_Shader.setMat4("projection", projection);
	m_Shader.setVec3("viewPos", cameraPosition);

	m_Shader.setFloat("brightness", m_Brightness);

	glBindVertexArray(m_VAO);

	glDrawElements(GL_TRIANGLES, GLsizei(m_IndicesCount), GL_UNSIGNED_INT, 0);
}

Light LightSource::GetLightParams()
{
	return m_LightParams;
}

void LightSource::ChangeBrightness(float newValue)
{
	m_Brightness = newValue;
}
