#pragma once
#include "MayhemObjectHandle.h"
class SpotLightObjectHandle :
	public MayhemObjectHandle
{
public:
	explicit SpotLightObjectHandle(MayhemObjects* mayhemObjects, unsigned _int32 handleIndex) :
		MayhemObjectHandle(mayhemObjects, handleIndex) {}
	~SpotLightObjectHandle();
};

