#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

using glm::vec2, glm::vec3;
using glm::mat4;
using glm::quat;

class Transform
{
public:
	Transform(vec3 position, float pitch, float yaw, float roll, vec3 scale);
	Transform();

	void Rotate(vec3 rotation);

	mat4 GetTransformMatrix();
	vec3 GetPosition();
	vec3 GetScale();
	vec3 GetRightDirection();
	vec3 GetUpDirection();
	vec3 GetForwardDirection();
	quat GetOrientation();

	void SetPosition(vec3 newPosition);
	void SetScale(vec3 scale);

private:
	vec3 m_position{};
	float m_pitch, m_yaw, m_roll;
	vec3 m_scale{};
};