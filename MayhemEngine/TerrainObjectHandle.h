#pragma once
#include "DefaultObjectHandle.h"
class TerrainObjectHandle :
	public DefaultObjectHandle
{
public:
	TerrainObjectHandle(MayhemObjects* mayhemObjects, unsigned _int32 handleIndex) :
		DefaultObjectHandle(mayhemObjects, handleIndex) {}
	~TerrainObjectHandle();

	bool SetGridSize(const glm::vec2 gridSize);
	bool SetAltitudeScale(const float altitudeScale);
	bool AddTexturePath(const std::string path);
	bool SetVertexCount(const int vertexCount);
	
	glm::vec2 GetGridSize() const;
	float GetAltitudeScale() const;
	std::string  GetTexturePath(unsigned int index) const;
	int GetVertexCount() const;
};

