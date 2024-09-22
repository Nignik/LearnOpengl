#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <memory>
#include <vector>

#include "../Transform.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float ZOOM = 45.0f;

class Camera
{
public:
	Camera();

	mat4 GetViewMatrix();
	std::shared_ptr<Transform> GetSharedTransform();
	float GetZoom();
	vec3 GetPosition();

	void ProcessMouseScroll(float yoffset);

private:
	std::shared_ptr<Transform> m_Transform;

	float m_Zoom;
};
