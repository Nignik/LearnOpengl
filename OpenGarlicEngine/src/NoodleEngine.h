#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <map>

#include "Camera/Camera.h"
#include "Camera/CameraController.h"
#include "InputHandler.h"
#include "EngineObjects/Line.h"
#include "NoodleGui.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

struct FrameData
{
	float deltaTime;
	glm::mat4 projection;
	glm::mat4 view;
	glm::vec3 position;
};

constexpr unsigned int SCR_WIDTH = 1200;
constexpr unsigned int SCR_HEIGHT = 800;

class NoodleEngine
{
public:
	NoodleEngine();
	~NoodleEngine();

	void StartFrame();
	void EndFrame();
	bool IsRunning();

	FrameData GetFrameData();
	GLFWwindow* GetWindow();
	

private:
	GLFWwindow* m_Window;
	std::shared_ptr<Camera> m_Camera;
	CameraController* m_CameraController;
	float m_DeltaTime = 0.0f;
	float m_LastFrame = 0.0f;

	GLFWwindow* windowInit();
	static void frameBuffer_Size_Callback(GLFWwindow* window, int width, int height);
};
