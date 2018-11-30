#pragma once
#include "MayhemObjectHandle.h"
class DirectionLightObjectHandle :
	public MayhemObjectHandle
{
public:
	explicit DirectionLightObjectHandle(MayhemObjects* mayhemObjects, unsigned _int32 handleIndex) :
		MayhemObjectHandle(mayhemObjects, handleIndex) {}

	~DirectionLightObjectHandle();
};

