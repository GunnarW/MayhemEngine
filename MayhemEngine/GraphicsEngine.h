#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Shader.h"
#include "MayhemObjectHandle.h"
#include "Camera.h"
#include "InputManager.h"
#include "Renderer.h"

//#include "GlobalHandleTable.h"

class GraphicsEngine
{
public:
	GraphicsEngine(const unsigned int width = 800, const unsigned int height = 600, char* windowName = "Mayhem Engine");
	~GraphicsEngine();
	void Initialize();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void Update(double dt);
	void Render();

	void AddObjectHandler(MayhemObjectHandle* handle);
	void LoadModel(MayhemObjectHandle* handle, std::string path);
	void InitializeShader(MayhemObjectHandle* handle);

	// getters
	GLFWwindow* GetWindow() const;

private:
	void ClearScreen();

	char* windowName;
	GLFWwindow* m_window;
	Renderer	m_renderer;
	Camera								m_camera;
	GLuint								m_VBO;
	GLuint								m_VAO;
	Shader*								standardShader;
	glm::mat4							m_view;
	glm::mat4							m_projection;
	unsigned int						m_height;
	unsigned int						m_width;
	std::vector<MayhemObjectHandle*>	m_objectHandles;
};

