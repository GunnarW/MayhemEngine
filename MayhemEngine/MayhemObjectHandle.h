#pragma once
#include "MayhemObject.h"
static const unsigned _int32 MAX_GAME_OBJECTS = 1024;
static MayhemObject* g_apGameObject[MAX_GAME_OBJECTS];

class MayhemObjectHandle
{
public:
	MayhemObjectHandle();
	~MayhemObjectHandle();

private:
	unsigned _int32 m_handleIndex;
	
};

