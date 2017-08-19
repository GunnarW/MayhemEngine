#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <atomic>

// Mayhem Classes
#include "Shader.h"
//#include "GlobalHandleTable.h"

class MayhemObject
{
public:
	MayhemObject();
	~MayhemObject();

	void LoadTexture(const char* filePath = "");

	void Update(double dt);

	void SetEnabled(bool enabled);

	void Render(const glm::mat4 projection, const glm::mat4 view);

	void SetPosition(const glm::vec3 postion);
	
	// Getters
	glm::mat4 GetModel() const;

protected:
	static std::atomic<unsigned _int32> s_uniqueId;

private:
	unsigned _int32 m_uniqueId;
	unsigned _int32 m_handleIndex;

	// Graphics (to be moved)
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

	int FindFreeSlotInHandleTable();
	friend class MayhemObjectHandle;

};

