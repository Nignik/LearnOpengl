#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <NoodleEngine.h>
#include <Shader/shader_m.h>
#include <EngineObjects/Line.h>
#include <Colors.h>
#include <stb_image.h>
#include <EngineObjects/shapes.h>
#include <EngineObjects/ObjectsGeneration.h>
#include <EngineObjects/PhysicsObject.h>
#include <EngineObjects/LightSource.h>

#include "Planetary.h"
using glm::vec3;

class GravitySimulation
{
public:
	GravitySimulation();

	void SwitchVelocityVectors();
	bool IsShowingVelocityVectors();
	void RenderFrame(FrameData& data);
	void ChangeSunBrightness(float newValue);
	void UpdateSatellitePosition(PhysicsObject& satellite, vec3 pivotPosition, float pivotMass, float deltaTime);

private:
	LightSource* m_LightSource;

	std::vector<PhysicsObject> m_Satellites;
	std::vector<Line> m_VelocityVectors;

	float m_GravitationalConstant = 0.0007f;

	bool m_ShowVelocityVectors = true;
};

inline glm::vec3 calculateGravitationalAcceleration(const Planet& primaryBody, const Planet& satellite)
{
	float gravitationalConstant = 0.0007f;

	float distance = glm::distance(primaryBody.position, satellite.position);
	glm::vec3 unitDirection = glm::normalize(primaryBody.position - satellite.position);

	glm::vec3 gravitationalAcceleration = unitDirection * gravitationalConstant * primaryBody.mass / (distance * distance);
	return gravitationalAcceleration;
}