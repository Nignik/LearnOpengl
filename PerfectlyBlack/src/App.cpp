#include <IncludeEngine.h>

#include <glm/gtc/random.hpp>
#include <rapidcsv.h>

constexpr double h = 6.62607015e-34;
constexpr double c = 2.99792458e8;
constexpr double k = 1.380649e-23;

double gammaCorrection(double c)
{
	c = std::max(0.0, std::min(1.0, c));  // Clip to [0, 1]
	if (c <= 0.0031308)
		return 12.92 * c;
	else
		return 1.055 * std::pow(c, 1.0 / 2.4) - 0.055;
}

vec3 calculateColor(double T)
{
	double x = 0.0, y = 0.0;
	if (1667 <= T && T <= 4000)
		x = (-0.2661239e9 / (T * T * T)) - (0.2343589e6 / (T * T)) + (0.8776956e3 / T) + 0.179910;
	else if (4000 < T && T <= 25000)
		x = (-3.0258469e9 / (T * T * T)) + (2.1070379e6 / (T * T)) + (0.2226347e3 / T) + 0.240390;
	else
	{
		return vec3(0.0f, 0.0f, 0.0f);
	}

	if (1667 <= T && T <= 2222)
		y = (-1.1063814 * x * x * x) - (1.34811020 * x * x) + (2.18555832 * x) - 0.20219683;
	else if (2222 < T && T <= 4000)
		y = (-0.9549476 * x * x * x) - (1.37418593 * x * x) + (2.09137015 * x) - 0.16748867;
	else if (4000 < T && T <= 25000)
		y = (3.0817580 * x * x * x) - (5.87338670 * x * x) + (3.75112997 * x) - 0.37001483;
	else
	{
		return vec3(0.0f, 0.0f, 0.0f);
	}
		
	double Y = 1.0;
	double X = (Y / y) * x;
	double Z = (Y / y) * (1 - x - y);

	double R_linear = 3.2406 * X - 1.5372 * Y - 0.4986 * Z;
	double G_linear = -0.9689 * X + 1.8758 * Y + 0.0415 * Z;
	double B_linear = 0.0557 * X - 0.2040 * Y + 1.0570 * Z;

	double R = gammaCorrection(R_linear);
	double G = gammaCorrection(G_linear);
	double B = gammaCorrection(B_linear);

	int R8bit = static_cast<int>(std::round(std::min(std::max(R, 0.0), 1.0) * 255.0));
	int G8bit = static_cast<int>(std::round(std::min(std::max(G, 0.0), 1.0) * 255.0));
	int B8bit = static_cast<int>(std::round(std::min(std::max(B, 0.0), 1.0) * 255.0));

	return vec3(R8bit / 255.0f, G8bit / 255.0f, B8bit / 255.0f);
}

extern Global::ObjectsManager* g_objectsManager;
extern Global::PhysicsEngine* g_physicsEngine;

int main()
{
	NoodleEngine engine;
	NoodleGui gui(engine.GetWindow());

	g_physicsEngine->Init();
	g_objectsManager->Init();

	const std::shared_ptr<MCooker::LightMaterial> perfectBlack = std::make_shared<MCooker::LightMaterial>(
		vec3(1.0f, 1.0f, 1.0f),
		1.0f
	);

	auto mesh = Procedural::SphereMesh(2.0f);
	auto model = std::make_shared<Model>(mesh);

	std::shared_ptr<Transform> sharedTransform = std::make_shared<Transform>(vec3(0.0f), 0.0f, 0.0f, 0.0f, vec3(4.0f));
	std::shared_ptr<RigidBody> rigidBody = std::make_shared<RigidBody>(0.0f, vec3(0.0f), sharedTransform);
	std::shared_ptr<Collider> collider = std::make_shared<Collider>(mesh, sharedTransform);
	rigidBody->AddCollider(collider);
	auto blackBody = std::make_unique<PhysicsObject>(model, sharedTransform, rigidBody, perfectBlack);

	double t = 7000;
	double b = 0.002897;
	double lambda = b / t;
	glm::vec3 rgb = vec3(0.0f);

	vec3 color = calculateColor(t);

	auto recalculateLambda = [&](float newTemp) -> void {
		//lambda = b / newTemp;
		t = (double)newTemp;
		color = calculateColor(t);
		//std::cout << "Color: " << color.x << ", " << color.y << ", " << color.z << std::endl;
	};

	FloatSlider temperatureSlider = {
		.label = "Temperature",
		.func = recalculateLambda,
		.value = (float)t,
		.minValue = 1667.0f,
		.maxValue = 25000.0f
	};

	gui.AddSlider(std::move(temperatureSlider));

	while (engine.IsRunning())
	{
		engine.StartFrame();

		perfectBlack->SetColor(color);

		g_physicsEngine->Update();
		blackBody->Draw();

		gui.RenderFrame();
		engine.EndFrame();
	}

	g_physicsEngine->Shutdown();
	g_objectsManager->Shutdown();
}