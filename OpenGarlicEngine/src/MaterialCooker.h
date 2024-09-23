#pragma once

#include "Shader.h"
#include "Material.h"

#include <memory>

using glm::vec3;

namespace MCooker
{

	class DefaultMaterial : public Material
	{
	public:
		DefaultMaterial(vec3 ambient, vec3 diffuse, vec3 specular, float shininess)
			: Material(std::make_shared<Shader>("shaders/default_vertex.vs", "shaders/default_fragment.fs")),
			m_ambient(ambient),
			m_diffuse(diffuse),
			m_specular(specular),
			m_shininess(shininess)
		{}

		void Use() override
		{
			SetShaderParameter("material.ambient", m_ambient);
			SetShaderParameter("material.diffuse", m_diffuse);
			SetShaderParameter("material.specular", m_specular);
			SetShaderParameter("material.shininess", m_shininess);
			
			SetShaderParameter("light.position", vec3(0.0f));
			SetShaderParameter("light.ambient", vec3(0.4f));
			SetShaderParameter("light.diffuse", vec3(0.4f));
			SetShaderParameter("light.specular", vec3(0.4f));
		}

	private:
		vec3 m_ambient;
		vec3 m_diffuse;
		vec3 m_specular;

		float m_shininess;
	};

	class LightMaterial : public Material
	{
	public:
		LightMaterial(vec3 color, float brightness)
			: Material(std::make_shared<Shader>("shaders/default_light.vs", "shaders/default_light.fs")),
			m_color(color),
			m_brightness(brightness)
		{
		}

		void Use() override
		{
			SetShaderParameter("color", m_color);
			SetShaderParameter("brightness", m_brightness);
		}

		void SetBrightness(float newBrightness)
		{
			m_brightness = newBrightness;
		}
		void SetColor(vec3 newColor)
		{
			m_color = newColor;
		}

	private:
		vec3 m_color;
		
		float m_brightness;
	};

	/*const std::shared_ptr<DefaultMaterial> EMERALD = std::make_shared<DefaultMaterial>(
		vec3(0.0215f, 0.1745f, 0.0215f),
		vec3(0.07568f, 0.61424f, 0.07568f),
		vec3(0.633f, 0.727811f, 0.633f),
		0.6f
	);

	const std::shared_ptr<DefaultMaterial> JADE = std::make_shared<DefaultMaterial>(
		vec3(0.135f, 0.2225f, 0.1575f),
		vec3(0.54f, 0.89f, 0.63f),
		vec3(0.316228f, 0.316228f, 0.316228f),
		0.1f
	);

	const std::shared_ptr<DefaultMaterial> OBSIDIAN = std::make_shared<DefaultMaterial>(
		vec3(0.05375f, 0.05f, 0.06625f),
		vec3(0.18275f, 0.17f, 0.22525f),
		vec3(0.332741f, 0.328634f, 0.346435f),
		0.3f
	);

	const std::shared_ptr<DefaultMaterial> PEARL = std::make_shared<DefaultMaterial>(
		vec3(0.25f, 0.20725f, 0.20725f),
		vec3(1.0f, 0.829f, 0.829f),
		vec3(0.296648f, 0.296648f, 0.296648f),
		0.088f
	);

	const std::shared_ptr<DefaultMaterial> RUBY = std::make_shared<DefaultMaterial>(
		vec3(0.1745f, 0.01175f, 0.01175f),
		vec3(0.61424f, 0.04136f, 0.04136f),
		vec3(0.727811f, 0.626959f, 0.626959f),
		0.6f
	);

	const std::shared_ptr<DefaultMaterial> TURQUOISE = std::make_shared<DefaultMaterial>(
		vec3(0.1f, 0.18725f, 0.1745f),
		vec3(0.396f, 0.74151f, 0.69102f),
		vec3(0.297254f, 0.30829f, 0.306678f),
		0.1f
	);

	const std::shared_ptr<DefaultMaterial> BRASS = std::make_shared<DefaultMaterial>(
		vec3(0.329412f, 0.223529f, 0.027451f),
		vec3(0.780392f, 0.568627f, 0.113725f),
		vec3(0.992157f, 0.941176f, 0.807843f),
		0.21794872f
	);

	const std::shared_ptr<DefaultMaterial> BRONZE = std::make_shared<DefaultMaterial>(
		vec3(0.2125f, 0.1275f, 0.054f),
		vec3(0.714f, 0.4284f, 0.18144f),
		vec3(0.393548f, 0.271906f, 0.166721f),
		0.2f
	);

	const std::shared_ptr<DefaultMaterial> CHROME = std::make_shared<DefaultMaterial>(
		vec3(0.25f, 0.25f, 0.25f),
		vec3(0.4f, 0.4f, 0.4f),
		vec3(0.774597f, 0.774597f, 0.774597f),
		0.6f
	);

	const std::shared_ptr<DefaultMaterial> COPPER = std::make_shared<DefaultMaterial>(
		vec3(0.19125f, 0.0735f, 0.0225f),
		vec3(0.7038f, 0.27048f, 0.0828f),
		vec3(0.256777f, 0.137622f, 0.086014f),
		0.1f
	);

	const std::shared_ptr<DefaultMaterial> GOLD = std::make_shared<DefaultMaterial>(
		vec3(0.24725f, 0.1995f, 0.0745f),
		vec3(0.75164f, 0.60648f, 0.22648f),
		vec3(0.628281f, 0.555802f, 0.366065f),
		0.4f
	);

	const std::shared_ptr<DefaultMaterial> SILVER = std::make_shared<DefaultMaterial>(
		vec3(0.19225f, 0.19225f, 0.19225f),
		vec3(0.50754f, 0.50754f, 0.50754f),
		vec3(0.508273f, 0.508273f, 0.508273f),
		0.4f
	);

	const std::shared_ptr<DefaultMaterial> BLACK_PLASTIC = std::make_shared<DefaultMaterial>(
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.01f, 0.01f, 0.01f),
		vec3(0.5f, 0.5f, 0.5f),
		0.25f
	);

	const std::shared_ptr<DefaultMaterial> CYAN_PLASTIC = std::make_shared<DefaultMaterial>(
		vec3(0.0f, 0.1f, 0.06f),
		vec3(0.0f, 0.50980392f, 0.50980392f),
		vec3(0.50196078f, 0.50196078f, 0.50196078f),
		0.25f
	);

	const std::shared_ptr<DefaultMaterial> GREEN_PLASTIC = std::make_shared<DefaultMaterial>(
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.1f, 0.35f, 0.1f),
		vec3(0.45f, 0.55f, 0.45f),
		0.25f
	);

	const std::shared_ptr<DefaultMaterial> RED_PLASTIC = std::make_shared<DefaultMaterial>(
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.5f, 0.0f, 0.0f),
		vec3(0.7f, 0.6f, 0.6f),
		0.25f
	);

	const std::shared_ptr<DefaultMaterial> WHITE_PLASTIC = std::make_shared<DefaultMaterial>(
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.55f, 0.55f, 0.55f),
		vec3(0.7f, 0.7f, 0.7f),
		0.25f
	);

	const std::shared_ptr<DefaultMaterial> YELLOW_PLASTIC = std::make_shared<DefaultMaterial>(
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.5f, 0.5f, 0.0f),
		vec3(0.6f, 0.6f, 0.5f),
		0.25f
	);

	const std::shared_ptr<DefaultMaterial> BLACK_RUBBER = std::make_shared<DefaultMaterial>(
		vec3(0.02f, 0.02f, 0.02f),
		vec3(0.01f, 0.01f, 0.01f),
		vec3(0.4f, 0.4f, 0.4f),
		0.078125f
	);

	const std::shared_ptr<DefaultMaterial> CYAN_RUBBER = std::make_shared<DefaultMaterial>(
		vec3(0.0f, 0.05f, 0.05f),
		vec3(0.4f, 0.5f, 0.5f),
		vec3(0.04f, 0.7f, 0.7f),
		0.078125f
	);

	const std::shared_ptr<DefaultMaterial> GREEN_RUBBER = std::make_shared<DefaultMaterial>(
		vec3(0.0f, 0.05f, 0.0f),
		vec3(0.4f, 0.5f, 0.4f),
		vec3(0.04f, 0.7f, 0.04f),
		0.078125f
	);

	const std::shared_ptr<DefaultMaterial> RED_RUBBER = std::make_shared<DefaultMaterial>(
		vec3(0.05f, 0.0f, 0.0f),
		vec3(0.5f, 0.4f, 0.4f),
		vec3(0.7f, 0.04f, 0.04f),
		0.078125f
	);

	const std::shared_ptr<DefaultMaterial> WHITE_RUBBER = std::make_shared<DefaultMaterial>(
		vec3(0.05f, 0.05f, 0.05f),
		vec3(0.5f, 0.5f, 0.5f),
		vec3(0.7f, 0.7f, 0.7f),
		0.078125f
	);

	const std::shared_ptr<DefaultMaterial> YELLOW_RUBBER = std::make_shared<DefaultMaterial>(
		vec3(0.05f, 0.05f, 0.0f),
		vec3(0.5f, 0.5f, 0.4f),
		vec3(0.7f, 0.7f, 0.04f),
		0.078125f
	);*/
}


