#include "DefaultObjectHandle.h"



DefaultObjectHandle::~DefaultObjectHandle()
{
}

///////////////////////////// Setters ///////////////////////////////////////


bool DefaultObjectHandle::AddMesh(const Mesh mesh)
{
	if (ObjectExists()) {
		m_mayhemObjects->m_meshes[m_handleIndex].push_back(mesh);
		return true;
	}
	return false;
}
bool DefaultObjectHandle::AddTexture(const Texture texture)
{
	if (ObjectExists()) {
		m_mayhemObjects->m_texturesLoaded[m_handleIndex].push_back(texture);

		return true;
	}
	return false;
}
bool DefaultObjectHandle::SetDirectory(const std::string directory)
{
	if (ObjectExists()) {
		m_mayhemObjects->m_directories[m_handleIndex] = directory;
		return true;
	}
	return false;
}

///////////////////// Getters ///////////////////////////////////////////////////

std::vector<Mesh>* DefaultObjectHandle::GetMeshes() const
{
	if (ObjectExists()) {
		return &m_mayhemObjects->m_meshes[m_handleIndex];
	}
}

std::vector<Texture>* DefaultObjectHandle::GetTextures() const
{
	if (ObjectExists()) {
		return &m_mayhemObjects->m_texturesLoaded[m_handleIndex];
	}
}

std::string DefaultObjectHandle::GetDirectory() const
{
	if (ObjectExists()) {
		return m_mayhemObjects->m_directories[m_handleIndex];
	}
}