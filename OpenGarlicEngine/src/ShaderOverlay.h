#pragma once

#include <vector>

#include "Shader.h"
#include "Mesh.h"

class ShaderOverlay
{
public:
	template <typename T>
	ShaderOverlay(T&& screenQuad)
		: m_ScreenQuad(std::forward<T>(screenQuad))
	{
	}

	void AddShader(std::shared_ptr<Shader> shader);
	void Render();

private:
	std::vector<std::shared_ptr<Shader>> m_Shaders;
	Mesh m_ScreenQuad;
};