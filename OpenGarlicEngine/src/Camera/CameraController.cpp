#include "CameraController.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

CameraController::CameraController(std::shared_ptr<Camera> camera)
	: m_Camera(camera),
	lastX(400),
	lastY(300),
	firstMouse(true)
{
	m_CanMove = true;
}

void CameraController::processInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (m_CanMove)
	{
	}
}

void CameraController::onMouseMove(double xPosIn, double yPosIn)
{
	if (!m_CanMove)
	{
		return;
	}

	float xPos = static_cast<float>(xPosIn);
	float yPos = static_cast<float>(yPosIn);

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;
}

void CameraController::onScroll(double xOffset, double yOffset)
{
	if (m_CanMove)
	{
		m_Camera->ProcessMouseScroll(static_cast<float>(yOffset));
	}
}

void CameraController::Stop()
{
	m_CanMove = false;
	firstMouse = true;
}

void CameraController::Start()
{
	m_CanMove = true;
}
