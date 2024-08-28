#include <IncludeEngine.h>

#include "Scene.h"

using glm::vec3;
using glm::mat4;

int main()
{
	NoodleEngine engine;
	NoodleGui gui(engine.GetWindow());

	Scene scene;
	scene.PrepareScene(engine);

	while (engine.IsRunning())
	{
		engine.StartFrame();

		scene.Draw(engine);

		engine.EndFrame();
	}
}