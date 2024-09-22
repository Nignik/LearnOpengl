#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <map>

#include "Camera/Camera.h"
#include "Camera/CameraController.h"
#include "InputHandler.h"
#include "Line.h"
#include "NoodleGui.h"
#include "stb_image.h"
#include "Controller.h"
#include "ObjectsManager.h"
#include "FrameData.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

using glm::vec2, glm::vec3;
using glm::mat4;

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

	void GenerateFrameData();
	vec2 GetResolution();
	GLFWwindow* GetWindow();
	std::shared_ptr<Camera> GetCamera();
	std::shared_ptr<Controller> GetController();
	

private:
	GLFWwindow* m_Window;

	std::shared_ptr<Camera> m_Camera;
	std::shared_ptr<Controller> m_Controller;

	float m_DeltaTime = 0.0f;
	float m_LastFrame = 0.0f;

	GLFWwindow* windowInit();
	static void frameBuffer_Size_Callback(GLFWwindow* window, int width, int height);
};
