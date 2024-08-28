#pragma once

#include <glad/glad.h>

#include <glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/quaternion.hpp>

using glm::vec2, glm::vec3;
using glm::mat4;
using glm::quat;

class Transform
{
public:
	Transform(vec3 position, float pitch, float yaw, float roll, vec3 scale);

	void RotateByOffset(vec2 delta, float speed);

	mat4 GetTransformMatrix();
	vec3 GetPosition();
	vec3 GetScale();
	vec3 GetRightDirection();
	vec3 GetUpDirection();
	vec3 GetForwardDirection();
	quat GetOrientation();

	void SetPosition(vec3 newPosition);

private:
	vec3 m_Position;
	float m_Pitch, m_Yaw, m_Roll;
	vec3 m_Scale;
};