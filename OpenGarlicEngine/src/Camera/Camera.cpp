#include "Camera.h"

#include <iostream>

Camera::Camera()
	: m_Transform(std::make_shared<Transform>(vec3(0.0f), 0.0f, 0.0f, 0.0f, vec3(1.0f))),
	m_Zoom(ZOOM)
{
}

glm::mat4 Camera::GetViewMatrix()
{
	mat4 rotationMatrix = glm::mat4_cast(m_Transform->GetOrientation());
	mat4 viewMatrix = glm::translate(mat4(1.0f), m_Transform->GetPosition()) * rotationMatrix;
	return glm::inverse(viewMatrix);
}

std::shared_ptr<Transform> Camera::GetSharedTransform()
{
	return m_Transform;
}

float Camera::GetZoom()
{
	return m_Zoom;
}

vec3 Camera::GetPosition()
{
	return m_Transform->GetPosition();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	m_Zoom -= (float)yoffset;
	if (m_Zoom < 1.0f)
		m_Zoom = 1.0f;
	if (m_Zoom > 45.0f)
		m_Zoom = 45.0f;
}

