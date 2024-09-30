#pragma once

#include <glm/glm.hpp>

namespace Global
{
	struct FrameData
	{
		int frameCount;

		float deltaTime;
		float timeAcc;
		float fps;

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