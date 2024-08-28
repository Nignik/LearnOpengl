#include <glm.hpp>

#include <IncludeEngine.h>

int main()
{
	NoodleEngine engine;
	NoodleGui gui(engine.GetWindow());

	while (engine.IsRunning())
	{
		engine.StartFrame();



		engine.EndFrame();
	}
}