#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Shader.h"
#include "MayhemObject.h"
//#include "GlobalHandleTable.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	GraphicsEngine(const unsigned int width, const unsigned int height);
	~GraphicsEngine();
	void Initialize();
	void Update(double dt);
	void Render();

private:
	GLuint VBO;
	GLuint VAO;
	Shader* standardShader;
	glm::mat4 view;
	glm::mat4 projection;
	unsigned int height;
	unsigned int width;
	unsigned int texture1, texture2;
	MayhemObject* object;
	MayhemObject* object2;
};

