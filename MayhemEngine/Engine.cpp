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
}

void Engine::LoadGameObjects() {
	std::vector<ParsedObject> objects = m_sceneLoader.GetGameObjects();

	for (unsigned int i = 0; i < objects.size(); i++) {
		LoadGameObject(objects[i], i);
	}
}

void Engine::LoadGameObject(ParsedObject object, int handlerIndex)
{
	if (object.type == "pointLight")
	{
		CreatePointLightObject(object, handlerIndex);
	}
	else if (object.type == "directionLight")
	{
		CreateDirectionLightObject(object, handlerIndex);
	}
	else if (object.type == "spotLight")
	{
		CreateSpotLightObject(object, handlerIndex);
	}
	else if (object.type == "terrain")
	{
		CreateTerrainObject(object, handlerIndex);
	}
	else
	{
		CreateDefaultObject(object, handlerIndex);
	}

	m_graphicsEngine.AddObjectHandler(m_objectHandles[handlerIndex]);
	m_graphicsEngine.InitializeShader(m_objectHandles[handlerIndex], object.vs.c_str(), object.fs.c_str());

	m_objectHandles[handlerIndex]->SetPosition(object.position);
	m_objectHandles[handlerIndex]->SetTransform(glm::translate(m_objectHandles[handlerIndex]->GetTransform(), object.position));
	//m_objectHandles[handlerIndex]->SetTransform(glm::scale(m_objectHandles[handlerIndex]->GetTransform(), glm::vec3(1.0f, 1.0f, 1.0f)));

	m_objectHandles[handlerIndex]->SetEnabled(object.enable);
	
	m_objectHandles[handlerIndex]->SetAmbient(object.ambient);
	m_objectHandles[handlerIndex]->SetDiffuse(object.diffuse);
	m_objectHandles[handlerIndex]->SetSpecular(object.specular);

	m_objectHandles[handlerIndex]->SetDirection(object.direction);
}

void Engine::UpdateHandlers()
{
	for (unsigned int i = 0; i < m_objectHandles.size(); i++)
	{
		m_objectHandles[i]->Update(m_DT);
	}
}

void Engine::CreateDefaultObject(ParsedObject object, int handlerIndex)
{
	DefaultObjectHandle* mayhemObject = new DefaultObjectHandle(&objects, objects.CreateObject());
	m_objectHandles.push_back(mayhemObject);
	m_graphicsEngine.AddDefaultObjectHandler(mayhemObject);
	m_graphicsEngine.LoadModel(m_objectHandles[handlerIndex], object.objectFile.c_str());
}

void Engine::CreatePointLightObject(ParsedObject object, int handlerIndex)
{
	PointLightObjectHandle* mayhemObject = new PointLightObjectHandle(&objects, objects.CreateObject());
	m_objectHandles.push_back(mayhemObject);
	m_graphicsEngine.AddPointLightObjectHandler(mayhemObject);
}

void Engine::CreateDirectionLightObject(ParsedObject object, int handlerIndex)
{
	DirectionLightObjectHandle* mayhemObject = new DirectionLightObjectHandle(&objects, objects.CreateObject());
	m_objectHandles.push_back(mayhemObject);
	m_graphicsEngine.AddDirectionLightObjectHandler(mayhemObject);

	m_objectHandles[handlerIndex]->SetConstant(object.constant);
	m_objectHandles[handlerIndex]->SetLinear(object.linear);
	m_objectHandles[handlerIndex]->SetQuadratic(object.quadratic);
}

void Engine::CreateSpotLightObject(ParsedObject object, int handlerIndex)
{
	SpotLightObjectHandle* mayhemObject = new SpotLightObjectHandle(&objects, objects.CreateObject());
	m_objectHandles.push_back(mayhemObject);
	m_graphicsEngine.AddSpotLightObjectHandler(mayhemObject);

	m_objectHandles[handlerIndex]->SetConstant(object.constant);
	m_objectHandles[handlerIndex]->SetLinear(object.linear);
	m_objectHandles[handlerIndex]->SetQuadratic(object.quadratic);
	m_objectHandles[handlerIndex]->SetCutOff(object.cutOff);
	m_objectHandles[handlerIndex]->SetOuterCutOff(object.outerCutOff);
}

void Engine::CreateTerrainObject(ParsedObject object, int handlerIndex)
{
	TerrainObjectHandle* mayhemObject = new TerrainObjectHandle(&objects, objects.CreateObject());
	m_objectHandles.push_back(mayhemObject);
	m_graphicsEngine.AddTerrainObjectHandler(mayhemObject);

	mayhemObject->SetGridSize(object.gridSize);
	mayhemObject->SetAltitudeScale(object.altitudeScale);
	mayhemObject->AddTexturePath(object.texture);
	mayhemObject->AddTexturePath(object.slopeTexture);
	mayhemObject->AddTexturePath(object.heightmap);
	mayhemObject->SetVertexCount(object.vertexCount);

	m_graphicsEngine.GenerateTerrain(mayhemObject);
}
