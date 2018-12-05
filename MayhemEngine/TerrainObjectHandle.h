#pragma once
#include "MayhemObjectHandle.h"

class TerrainObjectHandle :
	public MayhemObjectHandle
{
public:
	explicit TerrainObjectHandle(MayhemObjects* mayhemObjects, unsigned _int32 handleIndex) :
		MayhemObjectHandle(mayhemObjects, handleIndex) {}
	~TerrainObjectHandle();
};

