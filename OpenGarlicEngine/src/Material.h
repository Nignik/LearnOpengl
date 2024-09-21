#pragma once

#include <glm.hpp>

#include "Shader.h"

using glm::vec3;
using glm::mat4;

template <class... T>
constexpr bool always_false = false;

class Material
{
public:
	Material(std::shared_ptr<Shader> shader)
		: m_shader(shader)
	{
	}

	virtual void Use() = 0;

	std::shared_ptr<Shader> GetShader()
	{
		return m_shader;
	};

	template <typename T>
	void SetShaderParameter(std::string name, T value)
	{
		if constexpr (std::is_same_v<T, bool>)
		{
			m_shader->SetBool(name, value);
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			m_shader->SetInt(name, value);
		}
		else if constexpr (std::is_same_v<T, float>)
		{
			m_shader->SetFloat(name, value);
		}
		else if constexpr (std::is_same_v<T, glm::vec2>)
		{
			m_shader->SetVec2(name, value);
		}
		else if constexpr (std::is_same_v<T, glm::vec3>)
		{
			m_shader->SetVec3(name, value);
		}
		else if constexpr (std::is_same_v<T, glm::vec4>)
		{
			m_shader->SetVec4(name, value);
		}
		else if constexpr (std::is_same_v<T, glm::mat2>)
		{
			m_shader->SetMat2(name, value);
		}
		else if constexpr (std::is_same_v<T, glm::mat3>)
		{
			m_shader->SetMat3(name, value);
		}
		else if constexpr (std::is_same_v<T, glm::mat4>)
		{
			m_shader->SetMat4(name, value);
		}
		else
		{
			static_assert(always_false<T>::value, "Unsupported type");
		}
	}

	void SetMVP(mat4 model, mat4 view, mat4 projection)
	{
		m_shader->SetMat4("model", model);
		m_shader->SetMat4("view", view);
		m_shader->SetMat4("projection", projection);
	}

protected:
	std::shared_ptr<Shader> m_shader;

	vec3 ambient{};
	vec3 diffuse{};
	vec3 specular{};

	float shininess{};
};