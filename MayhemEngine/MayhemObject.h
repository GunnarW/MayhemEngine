#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include "Shader.h"
#include <boost/atomic.hpp>

class MayhemObject
{
public:
	MayhemObject();
	~MayhemObject();

	void LoadTexture(const char* filePath = "");

	void Update(double dt);

	void SetEnabled(bool enabled);

	void Render(const glm::mat4 projection, const glm::mat4 view);
	
	// Getters
	glm::mat4 GetModel() const;

protected:
	static boost::atomic<unsigned _int32> m_uniqueId;
private:
	_int32 Id;
	glm::mat4 m_model;
	std::vector<float> m_mesh;

	glm::vec3 m_position;
	glm::quat m_rotation;
	std::vector<MayhemObject*> m_components;
	bool m_isEnabled;
	GLuint m_VBO;
	GLuint m_VAO;
	char* m_textureLoc;
	unsigned int m_texture;
	Shader* m_shader;
};

