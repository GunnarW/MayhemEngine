#include "TerrainObjectHandle.h"



TerrainObjectHandle::~TerrainObjectHandle()
{
}

bool TerrainObjectHandle::SetGridSize(const glm::vec2 gridSize)
{
	if (ObjectExists()) {
		m_mayhemObjects->m_gridSizes[m_handleIndex] = gridSize;
		return true;
	}
	return false;
}

bool TerrainObjectHandle::SetAltitudeScale(const float altitudeScale)
{
	if (ObjectExists()) {
		m_mayhemObjects->m_altitudeScale[m_handleIndex] = altitudeScale;
		return true;
	}
	return false;
}

bool TerrainObjectHandle::AddTexturePath(const std::string path)
{
	if (ObjectExists()) {
		m_mayhemObjects->m_texturePath[m_handleIndex].push_back(path);
		return true;
	}
	return false;
}

bool TerrainObjectHandle::SetVertexCount(const int vertexCount)
{
	if (ObjectExists()) {
		m_mayhemObjects->m_vertexCount[m_handleIndex] = vertexCount;
		return true;
	}
	return false;
}

glm::vec2 TerrainObjectHandle::GetGridSize() const
{
	return m_mayhemObjects->m_gridSizes[m_handleIndex];
}

float TerrainObjectHandle::GetAltitudeScale() const
{
	return m_mayhemObjects->m_altitudeScale[m_handleIndex];
}

std::string  TerrainObjectHandle::GetTexturePath(unsigned int index) const
{
	return m_mayhemObjects->m_texturePath[m_handleIndex][index];
}

int TerrainObjectHandle::GetVertexCount() const
{
	return m_mayhemObjects->m_vertexCount[m_handleIndex];
}
