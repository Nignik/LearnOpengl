#include "GravitySimulation.h"

#include "MaterialCooker.h"

using glm::vec3;

GravitySimulation::GravitySimulation()
{
	Shader g_SatelliteShader("shaders/physicsVertex.vs", "shaders/physicsFragment.fs");
	Shader g_SunShader("shaders/lightVertex.vs", "shaders/lightFragment.fs");

	const int sphereSectorCount = 40;
	const int sphereStackCount = 30;

	std::vector<Material> planetMaterials = { MCooker::EMERALD, MCooker::YELLOW_RUBBER, MCooker::EMERALD, MCooker::YELLOW_RUBBER, MCooker::EMERALD };

	std::vector<Vertex> vertices = sphere::generateVertices(0.5f);
	std::vector<int> indices = std::get<0>(sphere::generateIndices());
	auto [VBO, VAO, EBO] = generateObjects(vertices, indices);

	glm::vec3 position(0.0f, 0.0f, 0.0f);
	glm::vec3 ambient(0.7f, 0.7f, 0.7f);
	glm::vec3 diffuse(0.5f, 0.5f, 0.5f);
	glm::vec3 specular(1.0f, 1.0f, 1.0f);
	Light light = { position, ambient, diffuse, specular };

	m_LightSource = new LightSource(vec3(0.0f), g_SunShader, VBO, VAO, EBO, indices.size(), light, 0.5f);

	for (int i = 0; i < 5; i++)
	{
		auto planetPosition = glm::vec3(4.0f + i, 0.0f, -5.0f - i);
		auto planetVelocity = glm::vec3(1.0f, 0.0f, 0.0f);
		m_Satellites.emplace_back(MCooker::YELLOW_RUBBER, planetPosition, VBO, VAO, EBO, indices.size(), g_SatelliteShader, 0.0f, planetVelocity);
	}

	for (int i = 0; i < 5; i++)
	{
		glm::vec3 start = glm::vec3(0.0f), end = m_Satellites[i].GetVelocity();
		std::vector<float> vertices = { start.x, start.y, start.z, end.x, end.y, end.z };
		m_VelocityVectors.emplace_back(vertices, m_Satellites[i].GetPosition());
	}
}

void GravitySimulation::SwitchVelocityVectors()
{
	m_ShowVelocityVectors = !m_ShowVelocityVectors;
}

bool GravitySimulation::IsShowingVelocityVectors()
{
	return m_ShowVelocityVectors;
}

void GravitySimulation::RenderFrame(FrameData& data)
{
	auto& [deltaTime, projection, view, cameraPosition] = data;

	m_LightSource->Draw(projection, view, cameraPosition, m_LightSource->GetLightParams());
	
	for (auto & sat : m_Satellites)
	{
		UpdateSatellitePosition(sat, vec3(0.0f), 10000.0f, deltaTime);
		sat.Draw(projection, view, cameraPosition, m_LightSource->GetLightParams());
	}

	if (m_ShowVelocityVectors)
	{
		for (size_t i = 0; i < m_VelocityVectors.size(); i++)
		{
			m_VelocityVectors[i].Update(m_Satellites[i].GetPosition(), m_Satellites[i].GetPosition() + m_Satellites[i].GetVelocity());
			m_VelocityVectors[i].Draw(projection, view);
		}
	}
}

void GravitySimulation::ChangeSunBrightness(float newValue)
{
	m_LightSource->ChangeBrightness(newValue);
}

void GravitySimulation::UpdateSatellitePosition(PhysicsObject& satellite, vec3 pivotPosition, float pivotMass, float deltaTime)
{
	const float distance = glm::distance(satellite.GetPosition(), pivotPosition);
	const glm::vec3 unitDirection = glm::normalize(pivotPosition - satellite.GetPosition());

	const glm::vec3 gravitationalAcceleration = unitDirection * m_GravitationalConstant * pivotMass / (distance * distance);
	satellite.SetVelocity(satellite.GetVelocity() + gravitationalAcceleration * deltaTime);
	satellite.SetPosition(satellite.GetPosition() + satellite.GetVelocity() * deltaTime);
}
