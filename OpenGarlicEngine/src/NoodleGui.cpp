#include "NoodleGui.h"
#include <iostream>

NoodleGui::NoodleGui(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
}

NoodleGui::~NoodleGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void NoodleGui::RenderFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	for (auto& button : buttons)
	{
		if (ImGui::Button((button.label).c_str()))
		{
			button.func();
		}
	}

	for (auto& slider : sliders)
	{
		if (ImGui::SliderFloat((slider.label).c_str(), &slider.value, slider.minValue, slider.maxValue))
		{
			slider.func(slider.value);
		}
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void NoodleGui::ShowControllerSettings(std::weak_ptr<Controller> controller)
{
	if (auto locked = controller.lock())
	{
		FloatSlider new_slider("movement speed", [&](float new_speed) {locked->SetMovementSpeed(new_speed); }, 100.0f, 0.1f, 300.0f);
		AddSlider(std::move(new_slider));
	}
	else
	{
		std::cerr << "Controller doesn't possess any objects" << std::endl;
	}
	
}

void NoodleGui::AddButton(Butt&& newButton)
{
	buttons.push_back(std::move(newButton));
}

void NoodleGui::AddSlider(FloatSlider&& newSlider)
{
	sliders.push_back(newSlider);
	FloatSlider& currentSlider = sliders.back();
	currentSlider.func(currentSlider.value);
}



