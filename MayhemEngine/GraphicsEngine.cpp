#include "GraphicsEngine.h"



GraphicsEngine::GraphicsEngine(const unsigned int width, const unsigned  int height, char* windowName) : m_width(width), m_height(height), windowName(windowName)
{
	Initialize();
}

GraphicsEngine::~GraphicsEngine()
{
	delete standardShader;
	delete windowName;
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

void GraphicsEngine::Initialize()
{
	InputManager &inputManager = InputManager::GetInstance();
	inputManager.Initialize(&m_camera);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(this->m_width, this->m_height, windowName, NULL, NULL);
	if (m_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	glfwSetKeyCallback(m_window, &InputManager::StaticKeyPressedCallback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	m_shader.Initialize("Shaders/stdShader.vs", "Shaders/stdShader.fs");
}

void GraphicsEngine::Update(double DT) 
{
	m_camera.Update(DT);
}

void GraphicsEngine::Render() 
{
	ClearScreen();
	glfwPollEvents();
	glm::mat4 view;
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, 0.1f, 100.0f);
	glm::vec3 cameraPos = m_camera.GetPosition();
	glm::vec3 negativeCameraPosition = glm::vec3(-cameraPos.x, -cameraPos.y, -cameraPos.z);
	view = glm::translate(view, negativeCameraPosition);


	m_shader.SetMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	m_shader.SetMat4("view", view);

	m_shader.SetVec3("cameraPosition", cameraPos);

	m_shader.SetInt("numberPointLights", m_pointLightObjectHandles.size());
	
	for (unsigned _int32 i = 0; i < m_pointLightObjectHandles.size(); i++) {
		m_renderer.RenderPointLight(m_pointLightObjectHandles[i], i, &m_shader);
	}


	for (unsigned _int32 i = 0; i < m_defaultObjectHandles.size(); i++) {
		m_renderer.RenderDefault(m_defaultObjectHandles[i], &m_shader);
	}

	m_shader.Use();
}

void GraphicsEngine::ClearScreen()
{
	//glClearColor(222.0f/255.0f, 230.0f/255.0f, 1.0f, 1.0f);
	glClearColor(0,0,0, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsEngine::framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void GraphicsEngine::AddObjectHandler(MayhemObjectHandle* handle) 
{
	m_objectHandles.push_back(handle);
}

void GraphicsEngine::LoadModel(MayhemObjectHandle* handle, std::string path)
{
	m_renderer.LoadModel(handle, path);
}

void GraphicsEngine::InitializeShader(MayhemObjectHandle* handle, const char* vs, const char* fs)
{
}

GLFWwindow* GraphicsEngine::GetWindow() const 
{
	return m_window;
}

void GraphicsEngine::AddDefaultObjectHandler(DefaultObjectHandle* handle)
{
	m_defaultObjectHandles.push_back(handle);
}

void GraphicsEngine::AddPointLightObjectHandler(PointLightObjectHandle* handle)
{
	m_pointLightObjectHandles.push_back(handle);

}

void GraphicsEngine::AddDirectionLightObjectHandler(DirectionLightObjectHandle* handle)
{
	m_DirectionLightObjectHandles.push_back(handle);

}

void GraphicsEngine::AddSpotLightObjectHandler(SpotLightObjectHandle* handle)
{
	m_SpotLightObjectHandles.push_back(handle);

}