#include "NoodleEngine.h"

NoodleEngine::NoodleEngine()
	: m_Window(windowInit()),
	m_Camera(std::make_shared<Camera>()),
	m_CameraController(new CameraController(m_Camera))
{
	glfwSetWindowUserPointer(m_Window, m_CameraController);
	glEnable(GL_DEPTH_TEST);
}

NoodleEngine::~NoodleEngine()
{
	glfwTerminate();
}

void NoodleEngine::StartFrame()
{
	glfwPollEvents();

	float currentFrame = static_cast<float>(glfwGetTime());
	m_DeltaTime = currentFrame - m_LastFrame;
	m_LastFrame = currentFrame;

	m_CameraController->processInput(m_Window, m_DeltaTime);

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
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

FrameData NoodleEngine::GetFrameData()
{
	glm::mat4 projection = glm::perspective(glm::radians(m_Camera->Zoom), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, 100.0f);
	glm::mat4 view = m_Camera->GetViewMatrix();
	return FrameData(m_DeltaTime, projection, view, m_Camera->Position);
}

GLFWwindow* NoodleEngine::GetWindow()
{
	return m_Window;
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

	return window;
}

void NoodleEngine::frameBuffer_Size_Callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}


