#include "SkyboxObjectHandle.h"



SkyboxObjectHandle::~SkyboxObjectHandle()
{
}

bool SkyboxObjectHandle::AddTexturePath(const std::string path)
{
	if (ObjectExists()) {
		m_mayhemObjects->m_texturePath[m_handleIndex].push_back(path);
		return true;
	}
	return false;
}

std::vector<std::string> SkyboxObjectHandle::GetTexturePaths() const
{
	return m_mayhemObjects->m_texturePath[m_handleIndex];
}
