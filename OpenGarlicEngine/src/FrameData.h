#pragma once

#include <glm/glm.hpp>

namespace Global
{
	struct FrameData
	{
		float deltaTime;
		glm::mat4 projection;
		glm::mat4 view;
		glm::vec3 position;

		static FrameData& GetInstance()
		{
			static FrameData instance;
			return instance;
		}
	};
};