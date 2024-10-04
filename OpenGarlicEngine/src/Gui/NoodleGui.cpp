#include "NoodleGui.h"
#include <iostream>

NoodleGui::NoodleGui(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 450");
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

	for (auto& button : m_buttons)
	{
		if (ImGui::Button((button.label).c_str()))
		{
			button.func();
		}
	}

	for (auto& slider : m_sliders)
	{
		slider->Render();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void NoodleGui::ShowControllerSettings(std::weak_ptr<Controller> controller)
{
	if (auto locked = controller.lock())
	{
		auto new_slider = std::make_shared<TypedSlider<float>>("movement speed", [locked](float new_speed) {locked->SetMovementSpeed(new_speed);}, 100.0f, 0.1f, 300.0f);

		AddSlider(new_slider);
	}
	else
	{
		std::cerr << "Controller doesn't possess any objects" << std::endl;
	}
}

void NoodleGui::AddButton(Butt&& newButton)
{
	m_buttons.push_back(std::move(newButton));
}

void NoodleGui::AddSlider(std::shared_ptr<Slider> newSlider)
{
	m_sliders.push_back(newSlider);
}

