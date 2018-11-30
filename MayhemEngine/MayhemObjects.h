#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <atomic>

#include "Mesh.h"

static const _int32 MAX_GAME_OBJECTS = 1024;


class MayhemObjects
{
public:
	MayhemObjects();
	~MayhemObjects();

	unsigned _int32 CreateObject();

	bool RemoveObject();

	// Setters

	// Getters

protected:
	std::atomic<unsigned _int32> s_uniqueId;

private:
	// Handles all pointers for game objects
	unsigned _int32	m_uniqueId[MAX_GAME_OBJECTS];	//32 bits

	bool	m_enabled[MAX_GAME_OBJECTS];	// 8 bits each

	float	m_constant[MAX_GAME_OBJECTS];
	float	m_linear[MAX_GAME_OBJECTS];
	float	m_quadratic[MAX_GAME_OBJECTS];
	float	m_cutOff[MAX_GAME_OBJECTS];
	float	m_outerCutOff[MAX_GAME_OBJECTS];
	
	glm::vec3	m_position[MAX_GAME_OBJECTS];
	glm::vec3	m_direction[MAX_GAME_OBJECTS];
	glm::vec3	m_ambient[MAX_GAME_OBJECTS];
	glm::vec3	m_diffuse[MAX_GAME_OBJECTS];
	glm::vec3	m_specular[MAX_GAME_OBJECTS];
	glm::vec3	m_lightColor[MAX_GAME_OBJECTS];

	glm::quat	m_rotation[MAX_GAME_OBJECTS];
	
	std::vector<Mesh>	m_meshes[MAX_GAME_OBJECTS];
	
	std::vector<Texture>	m_texturesLoaded[MAX_GAME_OBJECTS];
	
	std::string	m_directories[MAX_GAME_OBJECTS];
	
	glm::mat4	m_transforms[MAX_GAME_OBJECTS];

	Shader	m_shaders[MAX_GAME_OBJECTS];

	friend class MayhemObjectHandle;
	friend class DefaultObjectHandle;
	friend class PointLightObjectHandle;
	friend class DirectionLightObjectHandle;
	friend class SpotLightObjectHandle;
};