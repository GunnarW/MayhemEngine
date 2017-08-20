#include "Engine.h"

Engine::Engine(const unsigned int width, const unsigned  int height, char* windowName) : width(width), height(height), windowName(windowName)
{
	
}

Engine::~Engine()
{
	delete graphicsComponent;
	graphicsComponent = NULL;
	delete enginePtr;
	delete windowName;
}

bool Engine::Initialize() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(this->width, this->height, windowName, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
	// Set up Graphics
	this->graphicsComponent = new GraphicsEngine(width, height);
	this->graphicsComponent->Initialize();


	// Test objects and handles
	MayhemObjectHandle* handle1 = new MayhemObjectHandle(&objects, objects.CreateObject());
	MayhemObjectHandle* handle2 = new MayhemObjectHandle(&objects, objects.CreateObject());
	MayhemObjectHandle* handle3 = new MayhemObjectHandle(&objects, objects.CreateObject());

	std::cout << handle1->ObjectExists() << std::endl;
	std::cout << handle2->ObjectExists() << std::endl;
	std::cout << handle3->ObjectExists() << std::endl;

	// set time running
	this->runTime = glfwGetTime();

	return true;
}

void Engine::Run() {
	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		ProcessInput(window);

		// set DT
		UpdateDT();
		
		// update components
		this->graphicsComponent->Update(DT);

		// Render changes
		this->graphicsComponent->Render();

		// Swap the screen buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	
}


void Engine::ProcessInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void Engine::UpdateDT() {
	DT = glfwGetTime() - runTime;
	runTime = glfwGetTime();
}

double Engine::GetDT() {
	return DT;
}