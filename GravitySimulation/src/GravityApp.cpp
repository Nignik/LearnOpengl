#include "GravitySimulation.h"
#include <NoodleEngine.h>
#include <NoodleGui.h>

int main()
{
	NoodleEngine noodleEngine;
	NoodleGui gui(noodleEngine.GetWindow());
	GravitySimulation simulation;

	gui.AddButton(Butt("Enable/Disable velocity vectors", [&] {simulation.SwitchVelocityVectors(); }));
	gui.AddSlider(FloatSlider(
		"Change sun brightness",
		[&](float newValue) {simulation.ChangeSunBrightness(newValue); },
		0.5f,
		0.0,
		1.0
	));

	while (noodleEngine.IsRunning())
	{
		noodleEngine.StartFrame();
		FrameData currentFrame = noodleEngine.GetFrameData();
		simulation.RenderFrame(currentFrame);
		gui.RenderFrame();
		noodleEngine.EndFrame();
	}
	
	return 0;
}