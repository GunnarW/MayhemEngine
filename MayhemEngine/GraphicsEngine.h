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

#include "MayhemGameHelper.h"

class GraphicsEngine
{
public:
	GraphicsEngine(const unsigned int width = 2048, const unsigned int height = 1080, char* windowName = "Mayhem Engine");
	~GraphicsEngine();
	void Initialize();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void Update(double dt);
	void Render();

	void AddObjectHandler(MayhemObjectHandle* handle);
	void LoadModel(MayhemObjectHandle* handle, std::string path);
	void InitializeShader(MayhemObjectHandle* handle, const char* vs, const char* fs);

	void AddDefaultObjectHandler(DefaultObjectHandle* handle);
	void AddPointLightObjectHandler(PointLightObjectHandle* handle);
	void AddDirectionLightObjectHandler(DirectionLightObjectHandle* handle);
	void AddSpotLightObjectHandler(SpotLightObjectHandle* handle);

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

	std::vector<MayhemObjectHandle*>			m_objectHandles;
	std::vector<DefaultObjectHandle*>			m_defaultObjectHandles;
	std::vector<PointLightObjectHandle*>		m_pointLightObjectHandles;
	std::vector<DirectionLightObjectHandle*>	m_directionLightObjectHandles;
	std::vector<SpotLightObjectHandle*>			m_spotLightObjectHandles;

	Shader m_shader;
};

