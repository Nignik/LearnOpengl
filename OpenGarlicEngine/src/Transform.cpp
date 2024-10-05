#include "Transform.h"


Transform::Transform(vec3 position, float pitch, float yaw, float roll, vec3 scale)
	: m_position(position),
	m_pitch(pitch),
	m_yaw(yaw),
	m_roll(roll),
	m_scale(scale)
{
}

Transform::Transform()
	: m_position(vec3(0.0f)),
	m_pitch(0.0f),
	m_yaw(0.0f),
	m_roll(0.0f),
	m_scale(vec3(1.0f))
{

}

void Transform::Rotate(vec3 rotation)
{
	m_yaw += rotation.x;
	m_pitch -= rotation.y;
	m_roll += rotation.z;

	/*m_Yaw = glm::clamp(m_Yaw, -glm::radians(89.0f), glm::radians(89.0f));
	m_Pitch = glm::clamp(m_Pitch, -glm::radians(89.0f), glm::radians(89.0f));
	m_Roll = glm::clamp(m_Roll, -glm::radians(89.0f), glm::radians(89.0f));*/
}

mat4 Transform::GetTransformMatrix()
{
	mat4 translation = glm::translate(glm::mat4(1.0f), m_position);

	mat4 rotationX = glm::rotate(mat4(1.0f), m_pitch, vec3(1.0f, 0.0f, 0.0f));
	mat4 rotationY = glm::rotate(mat4(1.0f), m_yaw, vec3(0.0f, 1.0f, 0.0f));
	mat4 rotationZ = glm::rotate(mat4(1.0f), m_roll, vec3(0.0f, 0.0f, 1.0f));
	mat4 rotation = rotationY * rotationX * rotationZ;

	mat4 scaling = glm::scale(mat4(1.0f), m_scale);

	return translation * rotation * scaling;
}

vec3 Transform::GetPosition()
{
	return m_position;
}

vec3 Transform::GetScale()
{
	return m_scale;
}

vec3 Transform::GetRightDirection()
{
	return glm::rotate(GetOrientation(), vec3(1.0f, 0.0f, 0.0f));
}

vec3 Transform::GetUpDirection()
{
	return glm::rotate(GetOrientation(), vec3(0.0f, 1.0f, 0.0f));
}

vec3 Transform::GetForwardDirection()
{
	return glm::rotate(GetOrientation(), vec3(0.0f, 0.0f, -1.0f));
}

quat Transform::GetOrientation()
{
	return quat(vec3(-m_pitch, -m_yaw, 0.0f));
}

void Transform::SetPosition(vec3 newPosition)
{
	m_position = newPosition;
}

void Transform::SetScale(vec3 scale)
{
	m_scale = scale;
}
