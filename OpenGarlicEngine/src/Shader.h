#pragma once

#include <glad/glad.h>
#include <glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using glm::vec2, glm::vec3, glm::vec4;
using glm::mat2, glm::mat3, glm::mat4;

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

	void Use();
	virtual void SetUniforms();

	unsigned int GetId();

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;

	void SetVec2(const std::string& name, const vec2& value) const;
	void SetVec2(const std::string& name, float x, float y) const;

	void SetVec3(const std::string& name, const vec3& value) const;
	void SetVec3(const std::string& name, float x, float y, float z) const;
		 
	void SetVec4(const std::string& name, const vec4& value) const;
	void SetVec4(const std::string& name, float x, float y, float z, float w);
		 
	void SetMat2(const std::string& name, const mat2& mat) const;
	void SetMat3(const std::string& name, const mat3& mat) const;
	void SetMat4(const std::string& name, const mat4& mat) const;

private:
	unsigned int m_ID;

	void CheckCompileErrors(GLuint shader, std::string type);
};
