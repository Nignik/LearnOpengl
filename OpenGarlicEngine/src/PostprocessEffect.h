#pragma once

#include <memory>

#include "Shader.h"

template <class... T>
constexpr bool always_falsee = false;

class PostprocessEffect
{
public:
	PostprocessEffect(std::shared_ptr<Shader> shader)
		: m_shader(shader)
	{}

	virtual void Use() {};

	template <typename T>
	void SetShaderParameter(std::string name, T value)
	{
		m_shader->Use();
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
			static_assert(always_falsee<T>::value, "Unsupported type");
		}
	}

private:
	std::shared_ptr<Shader> m_shader;
};