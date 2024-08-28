#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <map>
#include <string>
#include <functional>

#include "Transform.h"

class Controller
{
public:
	Controller(float movementSpeed = 100.0f, float cameraSpeed = 0.001f);

	void ProcessInput(GLFWwindow* window, float deltaTime);
	void OnMouseMove(double xPosIn, double yPosIn);

	void SetMovementSpeed(float newSpeed);

	void AddAction(std::function<void()> action, std::string name);
	void Possess(std::weak_ptr<Transform> newPossession);

	void Stop();
	void Start();


private:
	std::vector<std::weak_ptr<Transform>> m_PossessedObjects;
	std::map<std::string, std::function<void()>> m_Actions;
	float m_LastX = 400, m_LastY = 300;
	float m_MovementSpeed;
	float m_MouseSensitivity;
	bool m_FirstMouse = true;
	bool m_MovementEnabled = true;
};