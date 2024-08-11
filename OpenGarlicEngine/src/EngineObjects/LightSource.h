#pragma once

#include <glad/glad.h>
#include <glm.hpp>

#include "Drawable.h"
#include "../Shader/ShaderStructs.h"
#include "../Shader/shader_m.h"

using glm::vec3;

class LightSource : Drawable
{
public:
	LightSource(vec3 position, Shader& pShader, GLuint VBO, GLuint VAO, GLuint EBO, size_t indicesCount, Light lightParams, float brightness);

	void Draw(mat4& projection, mat4& view, vec3& cameraPosition, const Light& light) override;
	Light GetLightParams();

	void ChangeBrightness(float newValue);

private:
	Light m_LightParams;
	float m_Brightness;
};