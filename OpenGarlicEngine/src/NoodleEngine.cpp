#include "NoodleEngine.h"

NoodleEngine::NoodleEngine()
	: m_Window(windowInit()),
	m_Camera(std::make_shared<Camera>()),
	m_postProcessShader(std::make_shared<Shader>("shaders/depth_buffer.vs", "shaders/depth_buffer.fs"))
{
	m_Controller = std::make_shared<Controller>();
	m_Controller->Possess(m_Camera->GetSharedTransform());
	glfwSetWindowUserPointer(m_Window, m_Controller.get());

	InitDepthBuffer();
	InitQuad();

	m_postProcessShader->Use();
	m_postProcessShader->SetInt("depthTexture", 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

NoodleEngine::~NoodleEngine()
{
	glfwTerminate();
}

void NoodleEngine::StartFrame()
{
	GenerateFrameData();

	m_Controller->ProcessInput(m_Window);

	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void NoodleEngine::EndFrame()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);

	m_postProcessShader->Use();
	glBindVertexArray(m_quad);
	glBindTexture(GL_TEXTURE_2D, m_colorBuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

bool NoodleEngine::IsRunning()
{
	return !glfwWindowShouldClose(m_Window);
}

void NoodleEngine::GenerateFrameData()
{
	auto& frameData = Global::FrameData::GetInstance();

	float currentTime = static_cast<float>(glfwGetTime());
	frameData.deltaTime = currentTime - m_LastFrame;
	m_LastFrame = currentTime;

	frameData.projection = glm::perspective(glm::radians(m_Camera->GetZoom()), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 1000.0f);
	frameData.view = m_Camera->GetViewMatrix();
	frameData.position = m_Camera->GetPosition();
}

vec2 NoodleEngine::GetResolution()
{
	return {SCR_WIDTH, SCR_HEIGHT};
}

GLFWwindow* NoodleEngine::GetWindow()
{
	return m_Window;
}

std::shared_ptr<Camera> NoodleEngine::GetCamera()
{
	return m_Camera;
}

std::shared_ptr<Controller> NoodleEngine::GetController()
{
	return m_Controller;
}

GLFWwindow* NoodleEngine::windowInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBuffer_Size_Callback);
	glfwSetCursorPosCallback(window, mouse_Callback);
	glfwSetScrollCallback(window, scroll_Callback);
	glfwSetKeyCallback(window, key_Callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	stbi_set_flip_vertically_on_load(false);
	glEnable(GL_DEPTH_TEST);

	return window;
}

void NoodleEngine::InitDepthBuffer()
{
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	// Create a color attachment texture (for your rendered scene)
	glGenTextures(1, &m_colorBuffer);
	glBindTexture(GL_TEXTURE_2D, m_colorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorBuffer, 0);

	// Create a depth attachment texture
	glGenRenderbuffers(1, &m_depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void NoodleEngine::frameBuffer_Size_Callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}

void NoodleEngine::InitQuad()
{
	GLuint quadVBO;
	float quadVertices[] = {
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
			1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
			1.0f, -1.0f,  1.0f, 0.0f,
			1.0f,  1.0f,  1.0f, 1.0f
	};
	// Setup plane VAO
	glGenVertexArrays(1, &m_quad);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(m_quad);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glBindVertexArray(0);
}

