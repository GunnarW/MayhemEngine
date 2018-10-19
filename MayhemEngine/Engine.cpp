#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
	delete m_enginePtr;

}

bool Engine::Initialize() {
	// Set up Graphics
	m_graphicsEngine.Initialize();

	// Test objects and handles
	m_sceneLoader.LoadFile("testScene.json");
	m_sceneLoader.ParseScene();
	LoadGameObjects();

	// set time running
	this->m_runTime = glfwGetTime();

	return true;
}

void Engine::Run() {
	// Game loop
	while (!glfwWindowShouldClose(m_graphicsEngine.GetWindow()))
	{
		// input
		ProcessInput(m_graphicsEngine.GetWindow());

		// set DT
		UpdateDT();

		// update components
		UpdateHandlers();
		m_graphicsEngine.Update(m_DT);

		// Render changes
		m_graphicsEngine.Render();

		// Swap the screen buffers
		glfwSwapBuffers(m_graphicsEngine.GetWindow());
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


void Engine::UpdateDT()
{
	m_DT = glfwGetTime() - m_runTime;
	m_runTime = glfwGetTime();
}

double Engine::GetDT()
{
	return m_DT;
}

void Engine::CreateHandle()
{
	m_objectHandles.push_back(new MayhemObjectHandle(&objects, objects.CreateObject()));
}

void Engine::LoadGameObjects() {
	std::vector<ParsedObject> objects = m_sceneLoader.GetGameObjects();

	for (unsigned int i = 0; i < objects.size(); i++) {
		LoadGameObject(objects[i], i);
	}
}

void Engine::LoadGameObject(ParsedObject object, int handlerIndex)
{
	CreateHandle();
	m_graphicsEngine.AddObjectHandler(m_objectHandles[handlerIndex]);

	m_objectHandles[handlerIndex]->GetRenderableComponent()->Initialize();
	m_objectHandles[handlerIndex]->GetRenderableComponent()->LoadTexture(object.texture.c_str());
	m_objectHandles[handlerIndex]->SetPosition(object.position);
	m_objectHandles[handlerIndex]->SetEnabled(object.enable);
}

void Engine::UpdateHandlers()
{
	for (unsigned int i = 0; i < m_objectHandles.size(); i++)
	{
		m_objectHandles[i]->Update(m_DT);
	}
}