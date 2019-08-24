#include "GraphicsEngine.h"



GraphicsEngine::GraphicsEngine(const unsigned int width, const unsigned  int height, char* windowName) : m_width(width), m_height(height), windowName(windowName)
{
	Initialize();
}

GraphicsEngine::~GraphicsEngine()
{
	delete m_standardShader;
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
	glfwSetCursorPosCallback(m_window, &InputManager::StaticMouseCursorPosCallback);
	glfwSetMouseButtonCallback(m_window, &InputManager::StaticMousePressedCallback);
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
	m_terrainShader.Initialize("Shaders/terrainShader.vs", "Shaders/terrainShader.fs");
	m_skyboxShader.Initialize("Shaders/cubemapShader.vs", "Shaders/cubemapShader.fs");
	m_postProcessShader.Initialize("Shaders/postProcessShader.vs","Shaders/postProcessShader.fs");

	InitializeFrameBuffer();
}

void GraphicsEngine::Update(double DT) 
{
	//std::cout << "FPS "<<int(1.0 / DT) << std::endl;
	m_camera.Update(DT);
}

void GraphicsEngine::Render() 
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glEnable(GL_DEPTH_TEST); 
	ClearScreen();
	glfwPollEvents();

	glm::mat4 view;
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, 0.1f, 10000.0f);
	glm::vec3 cameraPos = m_camera.GetPosition();
	glm::vec3 cameraDir = m_camera.GetDirection();
	glm::vec3 cameraUpDir = m_camera.GetUpDirection();
	view = glm::lookAt(cameraPos, cameraPos + cameraDir, cameraUpDir);

	m_shader.Use();

	m_shader.SetMat4("projection", projection); 
	m_shader.SetMat4("view", view);
	m_shader.SetVec3("cameraPosition", cameraPos);

	m_shader.SetInt("numberPointLights", m_pointLightObjectHandles.size());
	m_shader.SetInt("numberDirectionLights", m_directionLightObjectHandles.size());
	m_shader.SetInt("numberSpotLights", m_spotLightObjectHandles.size());
	
	for (unsigned _int32 i = 0; i < m_pointLightObjectHandles.size(); i++) {
		if (m_pointLightObjectHandles[i]->IsEnabled())
		{
			m_renderer.RenderPointLight(m_pointLightObjectHandles[i], i, &m_shader);
		}
	}

	for (unsigned _int32 i = 0; i < m_directionLightObjectHandles.size(); i++) {
		if (m_directionLightObjectHandles[i]->IsEnabled())
		{
			m_renderer.RenderDirectionLight(m_directionLightObjectHandles[i], i, &m_shader);
		}
	}

	for (unsigned _int32 i = 0; i < m_spotLightObjectHandles.size(); i++) {

		if (m_spotLightObjectHandles[i]->IsEnabled())
		{
			m_renderer.RenderSpotLight(m_spotLightObjectHandles[i], i, &m_shader);
		}
	}
	for (unsigned _int32 i = 0; i < m_defaultObjectHandles.size(); i++) 
	{
		if (m_defaultObjectHandles[i]->IsEnabled())
		{
			m_renderer.RenderDefault(m_defaultObjectHandles[i], &m_shader);
		}
	}

	m_terrainShader.Use();

	m_terrainShader.SetMat4("projection", projection);
	m_terrainShader.SetMat4("view", view);
	m_terrainShader.SetVec3("cameraPosition", cameraPos);

	m_terrainShader.SetInt("numberPointLights", m_pointLightObjectHandles.size());
	m_terrainShader.SetInt("numberDirectionLights", m_directionLightObjectHandles.size());
	m_terrainShader.SetInt("numberSpotLights", m_spotLightObjectHandles.size());
	
	for (unsigned _int32 i = 0; i < m_terrainObjectHandles.size(); i++)
	{
		if (m_terrainObjectHandles[i]->IsEnabled())
		{
			m_renderer.RenderDefault(m_terrainObjectHandles[i], &m_terrainShader);
		}
	}

	for (unsigned _int32 i = 0; i < m_pointLightObjectHandles.size(); i++) {
		if (m_pointLightObjectHandles[i]->IsEnabled())
		{
			m_renderer.RenderPointLight(m_pointLightObjectHandles[i], i, &m_terrainShader);
		}
	}

	for (unsigned _int32 i = 0; i < m_directionLightObjectHandles.size(); i++) {
		if (m_directionLightObjectHandles[i]->IsEnabled())
		{
			m_renderer.RenderDirectionLight(m_directionLightObjectHandles[i], i, &m_terrainShader);
		}
	}

	for (unsigned _int32 i = 0; i < m_spotLightObjectHandles.size(); i++) {

		if (m_spotLightObjectHandles[i]->IsEnabled())
		{
			m_renderer.RenderSpotLight(m_spotLightObjectHandles[i], i, &m_terrainShader);
		}
	}

	glDepthFunc(GL_LEQUAL);
	m_skyboxShader.Use();
	view = glm::mat4(glm::mat3(m_camera.GetViewMatrix()));
	m_skyboxShader.SetMat4("projection", projection);
	m_skyboxShader.SetMat4("view", view);

	for (unsigned _int32 i = 0; i < m_skyboxObjectHandles.size(); i++) {

		if (m_skyboxObjectHandles[i]->IsEnabled())
		{
			m_renderer.RenderSkybox(m_skyboxObjectHandles[i], &m_skyboxShader);
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
							  // clear all relevant buffers
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);

	m_postProcessShader.Use();
	glBindTexture(GL_TEXTURE_2D, m_textureColorBuffer);
	glBindVertexArray(m_quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void GraphicsEngine::ClearScreen()
{
	glClearColor(0.53f, .8f, .92f, 1.0f);
	//glClearColor(0, 0, 0, 1.0f);

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

void GraphicsEngine::InitializeFrameBuffer()
{
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
							 // positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &m_quadVAO);
	glGenBuffers(1, &m_quadVBO);
	glBindVertexArray(m_quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glGenFramebuffers(1, &m_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	// create a color attachment texture
	glGenTextures(1, &m_textureColorBuffer);
	glBindTexture(GL_TEXTURE_2D, m_textureColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorBuffer, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &m_RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO); // now actually attach it
																								  // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLFWwindow* GraphicsEngine::GetWindow() const 
{
	return m_window;
}

void GraphicsEngine::AddDefaultObjectHandler(DefaultObjectHandle *handle)
{
	m_defaultObjectHandles.push_back(handle);
}

void GraphicsEngine::AddPointLightObjectHandler(PointLightObjectHandle *handle)
{
	m_pointLightObjectHandles.push_back(handle);

}

void GraphicsEngine::AddDirectionLightObjectHandler(DirectionLightObjectHandle *handle)
{
	m_directionLightObjectHandles.push_back(handle);

}

void GraphicsEngine::AddSpotLightObjectHandler(SpotLightObjectHandle *handle)
{
	m_spotLightObjectHandles.push_back(handle);

}

void GraphicsEngine::AddTerrainObjectHandler(TerrainObjectHandle *handle)
{
	m_terrainObjectHandles.push_back(handle);
}

void GraphicsEngine::GenerateTerrain(TerrainObjectHandle* handle)
{
	m_terrainGenerator.ConstructMesh(handle, &m_renderer);
}

void GraphicsEngine::AddSkyboxObjectHandler(SkyboxObjectHandle* handle)
{
	m_skyboxObjectHandles.push_back(handle);
}

void GraphicsEngine::GenerateSkybox(SkyboxObjectHandle *handle)
{
	m_skyboxGenerator.ConstructSkybox(handle, &m_renderer);
}

void GraphicsEngine::ConfigureShaders()
{
	m_skyboxShader.Use();
	m_skyboxShader.SetInt("skybox", 0);

	m_postProcessShader.Use();
	m_postProcessShader.SetInt("screenTexture",0);
}

