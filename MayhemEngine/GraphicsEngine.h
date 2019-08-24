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
#include "TerrainGenerator.h"
#include "SkyboxGenerator.h"

class GraphicsEngine
{
public:
	GraphicsEngine(const unsigned int width = 2048, const unsigned int height = 1080, char* windowName = "Mayhem Engine");
	~GraphicsEngine();
	void Initialize();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void Update(double dt);
	void Render();

	void ConfigureShaders();

	void AddObjectHandler(MayhemObjectHandle* handle);
	void LoadModel(MayhemObjectHandle* handle, std::string path);

	void GenerateTerrain(TerrainObjectHandle* handle);
	void GenerateSkybox(SkyboxObjectHandle *handle);

	void InitializeShader(MayhemObjectHandle* handle, const char* vs, const char* fs);
	void InitializeFrameBuffer();

	void AddDefaultObjectHandler(DefaultObjectHandle* handle);
	void AddPointLightObjectHandler(PointLightObjectHandle* handle);
	void AddDirectionLightObjectHandler(DirectionLightObjectHandle* handle);
	void AddSpotLightObjectHandler(SpotLightObjectHandle* handle);
	void AddTerrainObjectHandler(TerrainObjectHandle *handle);
	void AddSkyboxObjectHandler(SkyboxObjectHandle* handle);

	// getters
	GLFWwindow* GetWindow() const;

private:
	void ClearScreen();

	char* windowName;
	GLFWwindow* m_window;
	Renderer	m_renderer;
	TerrainGenerator m_terrainGenerator;
	SkyboxGenerator m_skyboxGenerator;

	Camera								m_camera;
	GLuint								m_VBO;
	GLuint								m_VAO;
	Shader*								m_standardShader;
	glm::mat4							m_view;
	glm::mat4							m_projection;
	unsigned int						m_height;
	unsigned int						m_width;

	unsigned int						m_frameBuffer;
	unsigned int						m_textureColorBuffer;
	unsigned int						m_RBO;
	unsigned int						m_quadVAO;
	unsigned int						m_quadVBO;

	std::vector<MayhemObjectHandle*>			m_objectHandles;
	std::vector<DefaultObjectHandle*>			m_defaultObjectHandles;
	std::vector<PointLightObjectHandle*>		m_pointLightObjectHandles;
	std::vector<DirectionLightObjectHandle*>	m_directionLightObjectHandles;
	std::vector<SpotLightObjectHandle*>			m_spotLightObjectHandles;
	std::vector<TerrainObjectHandle*>			m_terrainObjectHandles;
	std::vector<SkyboxObjectHandle*>			m_skyboxObjectHandles;

	Shader m_shader;
	Shader m_terrainShader;
	Shader m_skyboxShader;
	Shader m_postProcessShader;
};

