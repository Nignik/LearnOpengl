#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Camera/Camera.h"
#include "Controller.h"
#include "Slider.h"

#include <vector>
#include <string>
#include <functional>
#include <variant>

struct Butt
{
	std::string label;
	std::function<void()> func;
};

class NoodleGui
{
public:
	NoodleGui(GLFWwindow* window);
	~NoodleGui();

	void RenderFrame();
	void ShowControllerSettings(std::weak_ptr<Controller> controller);
	void AddButton(Butt&& newButton);
	
	void AddSlider(std::shared_ptr<Slider> newSlider);

private:
	std::vector<Butt> m_buttons;
	std::vector<std::shared_ptr<Slider>> m_sliders;
};
