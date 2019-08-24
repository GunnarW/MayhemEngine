#pragma once
#include "DefaultObjectHandle.h"
class SkyboxObjectHandle :
	public DefaultObjectHandle
{
public:
	SkyboxObjectHandle(MayhemObjects* mayhemObjects, unsigned _int32 handleIndex) :
		DefaultObjectHandle(mayhemObjects, handleIndex) {}
	~SkyboxObjectHandle();
	
	bool AddTexturePath(const std::string path);

	std::vector<std::string> GetTexturePaths() const;
};

