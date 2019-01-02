#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include "ScriptManager.h"
#include "SceneLoader.h"
#include "GraphicsEngine.h"
#include "MayhemObjects.h"
#include "MayhemObjectHandle.h"
#include "DefaultObjectHandle.h"
#include "PointLightObjectHandle.h"
#include "DirectionLightObjectHandle.h"
#include "SpotLightObjectHandle.h"
#include "TerrainObjectHandle.h"

class Engine
{
public:
	Engine();
	~Engine();

	bool Initialize();
	void Run();
	static void ProcessInput(GLFWwindow *window);
	void UpdateDT();
	double GetDT();


private:
	void CreateHandle();
	void LoadGameObjects();
	void LoadGameObject(ParsedObject object, int handlerIndex);
	void UpdateHandlers();
	void CreateDefaultObject(ParsedObject object, int handlerIndex);
	void CreatePointLightObject(ParsedObject object, int handlerIndex);
	void CreateDirectionLightObject(ParsedObject object, int handlerIndex);
	void CreateSpotLightObject(ParsedObject object, int handlerIndex);
	void CreateTerrainObject(ParsedObject object, int handlerIndex);
	
	Engine *m_enginePtr = 0;
	GLuint m_width;
	GLuint m_height;
	double m_DT;
	double m_runTime;
	// Components
	GraphicsEngine m_graphicsEngine;
	MayhemObjects objects;
	SceneLoader m_sceneLoader;
	static const unsigned _int32 MAX_GAME_OBJECTS = 1024;
	// Properties
	std::vector<MayhemObjectHandle*>	m_objectHandles;
};

