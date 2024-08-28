#pragma once

#include "Shader.h"

using glm::vec3;

namespace MCooker
{
	const Material EMERALD = {
	vec3(0.0215f, 0.1745f, 0.0215f),
	vec3(0.07568f, 0.61424f, 0.07568f),
	vec3(0.633f, 0.727811f, 0.633f),
	0.6f
	};

	const Material JADE = {
		vec3(0.135f, 0.2225f, 0.1575f),
		vec3(0.54f, 0.89f, 0.63f),
		vec3(0.316228f, 0.316228f, 0.316228f),
		0.1f
	};

	const Material OBSIDIAN = {
		vec3(0.05375f, 0.05f, 0.06625f),
		vec3(0.18275f, 0.17f, 0.22525f),
		vec3(0.332741f, 0.328634f, 0.346435f),
		0.3f
	};

	const Material PEARL = {
		vec3(0.25f, 0.20725f, 0.20725f),
		vec3(1.0f, 0.829f, 0.829f),
		vec3(0.296648f, 0.296648f, 0.296648f),
		0.088f
	};

	const Material RUBY = {
		vec3(0.1745f, 0.01175f, 0.01175f),
		vec3(0.61424f, 0.04136f, 0.04136f),
		vec3(0.727811f, 0.626959f, 0.626959f),
		0.6f
	};

	const Material TURQUOISE = {
		vec3(0.1f, 0.18725f, 0.1745f),
		vec3(0.396f, 0.74151f, 0.69102f),
		vec3(0.297254f, 0.30829f, 0.306678f),
		0.1f
	};

	const Material BRASS = {
		vec3(0.329412f, 0.223529f, 0.027451f),
		vec3(0.780392f, 0.568627f, 0.113725f),
		vec3(0.992157f, 0.941176f, 0.807843f),
		0.21794872f
	};

	const Material BRONZE = {
		vec3(0.2125f, 0.1275f, 0.054f),
		vec3(0.714f, 0.4284f, 0.18144f),
		vec3(0.393548f, 0.271906f, 0.166721f),
		0.2f
	};

	const Material CHROME = {
		vec3(0.25f, 0.25f, 0.25f),
		vec3(0.4f, 0.4f, 0.4f),
		vec3(0.774597f, 0.774597f, 0.774597f),
		0.6f
	};

	const Material COPPER = {
		vec3(0.19125f, 0.0735f, 0.0225f),
		vec3(0.7038f, 0.27048f, 0.0828f),
		vec3(0.256777f, 0.137622f, 0.086014f),
		0.1f
	};

	const Material GOLD = {
		vec3(0.24725f, 0.1995f, 0.0745f),
		vec3(0.75164f, 0.60648f, 0.22648f),
		vec3(0.628281f, 0.555802f, 0.366065f),
		0.4f
	};

	const Material SILVER = {
		vec3(0.19225f, 0.19225f, 0.19225f),
		vec3(0.50754f, 0.50754f, 0.50754f),
		vec3(0.508273f, 0.508273f, 0.508273f),
		0.4f
	};

	const Material BLACK_PLASTIC = {
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.01f, 0.01f, 0.01f),
		vec3(0.5f, 0.5f, 0.5f),
		0.25f
	};

	const Material CYAN_PLASTIC = {
		vec3(0.0f, 0.1f, 0.06f),
		vec3(0.0f, 0.50980392f, 0.50980392f),
		vec3(0.50196078f, 0.50196078f, 0.50196078f),
		0.25f
	};

	const Material GREEN_PLASTIC = {
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.1f, 0.35f, 0.1f),
		vec3(0.45f, 0.55f, 0.45f),
		0.25f
	};

	const Material RED_PLASTIC = {
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.5f, 0.0f, 0.0f),
		vec3(0.7f, 0.6f, 0.6f),
		0.25f
	};

	const Material WHITE_PLASTIC = {
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.55f, 0.55f, 0.55f),
		vec3(0.7f, 0.7f, 0.7f),
		0.25f
	};

	const Material YELLOW_PLASTIC = {
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.5f, 0.5f, 0.0f),
		vec3(0.6f, 0.6f, 0.5f),
		0.25f
	};

	const Material BLACK_RUBBER = {
		vec3(0.02f, 0.02f, 0.02f),
		vec3(0.01f, 0.01f, 0.01f),
		vec3(0.4f, 0.4f, 0.4f),
		0.078125f
	};

	const Material CYAN_RUBBER = {
		vec3(0.0f, 0.05f, 0.05f),
		vec3(0.4f, 0.5f, 0.5f),
		vec3(0.04f, 0.7f, 0.7f),
		0.078125f
	};

	const Material GREEN_RUBBER = {
		vec3(0.0f, 0.05f, 0.0f),
		vec3(0.4f, 0.5f, 0.4f),
		vec3(0.04f, 0.7f, 0.04f),
		0.078125f
	};

	const Material RED_RUBBER = {
		vec3(0.05f, 0.0f, 0.0f),
		vec3(0.5f, 0.4f, 0.4f),
		vec3(0.7f, 0.04f, 0.04f),
		0.078125f
	};

	const Material WHITE_RUBBER = {
		vec3(0.05f, 0.05f, 0.05f),
		vec3(0.5f, 0.5f, 0.5f),
		vec3(0.7f, 0.7f, 0.7f),
		0.078125f
	};

	const Material YELLOW_RUBBER = {
		vec3(0.05f, 0.05f, 0.0f),
		vec3(0.5f, 0.5f, 0.4f),
		vec3(0.7f, 0.7f, 0.04f),
		0.078125f
	};
}


