#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>
#include <atomic>

#include "Renderable.h"


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
	unsigned _int32		m_uniqueId[MAX_GAME_OBJECTS];	//32 bits

	bool				m_enabled[MAX_GAME_OBJECTS];	// 8 bits each

	glm::vec3			m_pos[MAX_GAME_OBJECTS];

	glm::quat			m_rotation[MAX_GAME_OBJECTS];

	Renderable			m_renderable[MAX_GAME_OBJECTS];

	friend class MayhemObjectHandle;
};