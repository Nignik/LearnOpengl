#include "Controller.h"

#include <iostream>

Controller::Controller(float movementSpeed, float cameraSpeed)
	: m_MovementSpeed(movementSpeed),
	m_MouseSensitivity(cameraSpeed)
{

}

void Controller::ProcessInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (m_MovementEnabled)
	{
		float velocity = m_MovementSpeed * deltaTime;
		
		for (auto& possession : m_PossessedObjects)
		{
			if (auto locked = possession.lock())
			{
				vec3 position = locked->GetPosition();
				vec3 forward = locked->GetForwardDirection();
				vec3 right = locked->GetRightDirection();

				if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
					locked->SetPosition(position + forward * velocity);
				if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
					locked->SetPosition(position - forward * velocity);
				if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
					locked->SetPosition(position - right * velocity);
				if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
					locked->SetPosition(position + right * velocity);
			}
			else
			{
				std::cerr << "Controller doesn't possess any objects" << std::endl;
			}
		}

		// TODO: Make it do what it is suppposed to do
		/*if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
			m_Actions["shoot"]();*/
		
	}
}

void Controller::OnMouseMove(double xPosIn, double yPosIn)
{
	if (!m_MovementEnabled)
	{
		return;
	}

	float xPos = static_cast<float>(xPosIn);
	float yPos = static_cast<float>(yPosIn);

	if (m_FirstMouse)
	{
		m_LastX = xPos;
		m_LastY = yPos;
		m_FirstMouse = false;
	}

	float xOffset = xPos - m_LastX;
	float yOffset = m_LastY - yPos;

	m_LastX = xPos;
	m_LastY = yPos;

	for (auto& possession : m_PossessedObjects)
	{
		if (auto locked = possession.lock())
		{
			locked->RotateByOffset({ xOffset, yOffset }, m_MouseSensitivity);
		}
		else
		{
			std::cerr << "Controller doesn't possess any objects" << std::endl;
		}
	}
}

void Controller::SetMovementSpeed(float newSpeed)
{
	m_MovementSpeed = newSpeed;
}

void Controller::AddAction(std::function<void()> action, std::string name)
{
	m_Actions[name] = action;
}

void Controller::Possess(std::weak_ptr<Transform> newPossession)
{
	m_PossessedObjects.push_back(newPossession);
}

void Controller::Stop()
{
	m_MovementEnabled = false;
	m_FirstMouse = true;
}

void Controller::Start()
{
	m_MovementEnabled = true;
}

