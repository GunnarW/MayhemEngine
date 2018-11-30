#pragma once
#include "MayhemObjectHandle.h"
class PointLightObjectHandle :
	public MayhemObjectHandle
{
public:
	explicit PointLightObjectHandle(MayhemObjects* mayhemObjects, unsigned _int32 handleIndex) :
		MayhemObjectHandle(mayhemObjects, handleIndex) {}
	~PointLightObjectHandle();
};

