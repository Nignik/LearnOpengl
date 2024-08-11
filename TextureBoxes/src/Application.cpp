#include <NoodleEngine.h>

#include <TextureManager.h>
#include <EngineObjects/TextureBox.h>
#include <vector>

int main()
{
	NoodleEngine engine;

	TextureManager textureManager;
	unsigned int containerTexture = textureManager.LoadTexture("resources/textures/container.jpg");

	std::vector<float> vertices = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	std::vector<int> indices = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	Shader boxShader("shaders/boxVertex.vs", "shaders/boxFragment.fs");
	TextureBox box(vertices, indices, containerTexture, boxShader);
	
	
	while (engine.IsRunning())
	{
		engine.StartFrame();
		box.Draw();
		engine.EndFrame();
	}
}