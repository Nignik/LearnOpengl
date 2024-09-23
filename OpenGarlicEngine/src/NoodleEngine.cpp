#include "NoodleEngine.h"

NoodleEngine::NoodleEngine()
	: m_Window(windowInit()),
	m_Camera(std::make_shared<Camera>())
{
	m_Controller = std::make_shared<Controller>();
	m_Controller->Possess(m_Camera->GetSharedTransform());
	glfwSetWindowUserPointer(m_Window, m_Controller.get());

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
	glfwPollEvents();

	GenerateFrameData();

	m_Controller->ProcessInput(m_Window);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void NoodleEngine::EndFrame()
{
	glfwSwapBuffers(m_Window);
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

void NoodleEngine::frameBuffer_Size_Callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}


