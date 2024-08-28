#include <IncludeEngine.h>

using glm::mat4;
using glm::vec3;
using namespace Color;

int main()
{
	float rotationSpeed = 0.0f;
	float rotation = 0.0f;
	float height = 0.0f;

	NoodleEngine engine;
	NoodleGui gui(engine.GetWindow());

	Shader shader("shaders/1.basicVertex.vs", "shaders/1.basicFragment.fs");
	Model model("resources/objects/gura/source/GuraCasual/Binary/Gura_Model.fbx");

	gui.ShowCameraSettings(engine.GetCamera());

	glm::vec3 modelRotation(0.0f, 0.0f, 0.0f);
	FloatSlider xSlider("x axis rotation", [&](float newValue) {modelRotation.x = newValue; }, 0.0f, glm::pi<float>());
	FloatSlider ySlider("y axis rotation", [&](float newValue) {modelRotation.y = newValue; }, 0.0f, glm::pi<float>());
	FloatSlider zSlider("z axis rotation", [&](float newValue) {modelRotation.z = newValue; }, 0.0f, glm::pi<float>());
	FloatSlider rotationSpeedSlider("rotation speed", [&](float newValue) {rotationSpeed = newValue; }, rotation, 0.0f, 225.0f);

	gui.AddSlider(std::move(xSlider));
	gui.AddSlider(std::move(ySlider));
	gui.AddSlider(std::move(zSlider));
	gui.AddSlider(std::move(rotationSpeedSlider));

	Light light = { vec3(30.0f), vec3(0.4f), vec3(0.4f), vec3(0.4f) };

	shader.SetInt("material.diffuse", 0);
	shader.SetInt("material.specular", 1);

	while (engine.IsRunning())
	{
		engine.StartFrame();

		shader.Use();

		auto [deltaTime, projection, view, position] = engine.GetFrameData();
		auto newTransform = glm::mat4(1.0f);

		shader.SetMat4("projection", projection);
		shader.SetMat4("view", view);
		shader.SetMat4("model", newTransform);
		
		shader.SetFloat("material.shininess", 64.0f);

		shader.SetVec3("light.position", engine.GetCamera()->Position);
		shader.SetVec3("light.ambient", light.ambient);
		shader.SetVec3("light.diffuse", light.diffuse);
		shader.SetVec3("light.specular", light.specular);

		model.Draw(shader);

		gui.RenderFrame();

		engine.EndFrame();
	}
}