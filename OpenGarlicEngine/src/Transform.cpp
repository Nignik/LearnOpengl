#include "Transform.h"


Transform::Transform(vec3 position, float pitch, float yaw, float roll, vec3 scale)
	: m_Position(position),
	m_Pitch(pitch),
	m_Yaw(yaw),
	m_Roll(roll),
	m_Scale(scale)
{
}

void Transform::RotateByOffset(vec2 delta, float speed)
{
	delta.x *= speed;
	delta.y *= speed;

	m_Pitch -= delta.y;
	m_Yaw += delta.x;

	m_Pitch = glm::clamp(m_Pitch, -glm::radians(89.0f), glm::radians(89.0f));
}

mat4 Transform::GetTransformMatrix()
{
	mat4 translation = glm::translate(glm::mat4(1.0f), m_Position);

	mat4 rotationX = glm::rotate(mat4(1.0f), m_Pitch, vec3(1.0f, 0.0f, 0.0f));
	mat4 rotationY = glm::rotate(mat4(1.0f), m_Yaw, vec3(0.0f, 1.0f, 0.0f));
	mat4 rotationZ = glm::rotate(mat4(1.0f), m_Roll, vec3(0.0f, 0.0f, 1.0f));
	mat4 rotation = rotationY * rotationX * rotationZ;

	mat4 scaling = glm::scale(mat4(1.0f), m_Scale);

	return translation * rotation * scaling;
}

vec3 Transform::GetPosition()
{
	return m_Position;
}

vec3 Transform::GetScale()
{
	return m_Scale;
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
	return quat(vec3(-m_Pitch, -m_Yaw, 0.0f));
}

void Transform::SetPosition(vec3 newPosition)
{
	m_Position = newPosition;
}
