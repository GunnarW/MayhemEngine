#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include "MayhemObject.h"
#include "GraphicsEngine.h"

class Engine
{
public:
	Engine(const unsigned int width = 800, const unsigned int height = 600, char* windowName = "Mayhem Engine");
	~Engine();

	bool Initialize();
	void Run();
	static void ProcessInput(GLFWwindow *window);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void UpdateDT();
	double GetDT();

private:
	Engine *enginePtr = 0;
	GLuint width;
	GLuint height;
	char* windowName;
	GLFWwindow* window;
	std::vector<MayhemObject> mayhemObjects;
	double DT;
	double runTime;

	// Components
	GraphicsEngine *graphicsComponent;
};

