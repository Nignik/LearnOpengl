#include "ShaderOverlay.h"

void ShaderOverlay::AddShader(Shader&& shader)
{
	m_Shaders.push_back(shader);
}

void ShaderOverlay::Render()
{
	for (auto& shader : m_Shaders)
	{
		m_ScreenQuad.Draw(shader);
	}
}

