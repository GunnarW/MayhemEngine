#include "GraphicsEngine.h"



GraphicsEngine::GraphicsEngine()
{
}

GraphicsEngine::GraphicsEngine(const unsigned int width, const unsigned int height) : width(width), height(height)
{
}


GraphicsEngine::~GraphicsEngine()
{
	delete standardShader;

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void GraphicsEngine::Initialize() {
	// Vertex shader
	//standardShader = new Shader("Shaders/stdShader.vs","Shaders/stdShader.fs");

	this->object = new MayhemObject();
	this->object->LoadTexture("Textures/awesomeface.png");
}

void GraphicsEngine::Update(double dt) {


}

void GraphicsEngine::Render() {

	// Render
	// Clear the colorbuffer
	glClearColor(0.29f, 0.0f, 0.51f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 view;
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	this->object->Render(projection, view);
}
