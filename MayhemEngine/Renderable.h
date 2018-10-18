#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "shader.h"

class Renderable
{
public:
	Renderable();
	~Renderable();

	virtual void Initialize();

	void LoadTexture(const char* filePath = "");

	void Update(double dt);

	void Render(const glm::mat4 projection, const glm::mat4 view);

	glm::mat4 GetModel() const;

private:
	
	int CreateVAO();
	int UnbindBAO();
	
protected:
	unsigned int m_texture;
	GLuint m_VBO;		// 32bits
	GLuint m_VAO;
	glm::mat4 m_model;
	std::vector<float> m_mesh;
	Shader m_shader;
	char* m_textureLoc;
};

