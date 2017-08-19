#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>
#include <atomic>



static const _int32 MAX_GAME_OBJECTS = 1024;
class MayhemObjects
{
public: 
	MayhemObjects();
	~MayhemObjects();

	unsigned _int32 CreateObject();

	bool RemoveObject();

protected:
	std::atomic<unsigned _int32> s_uniqueId;

private:
	// Handles all pointers for game objects
	unsigned _int32	m_uniqueId[MAX_GAME_OBJECTS];	//32 bits
	unsigned _int32 m_textureLoc[MAX_GAME_OBJECTS];

	bool m_enabled[MAX_GAME_OBJECTS];	// 8 bits

	glm::vec3 m_pos[MAX_GAME_OBJECTS];

	glm::quat m_rotation[MAX_GAME_OBJECTS];

	friend class MayhemObjectHandle;

};