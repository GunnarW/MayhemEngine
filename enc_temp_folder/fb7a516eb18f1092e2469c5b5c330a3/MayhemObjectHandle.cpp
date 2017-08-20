#include "MayhemObjectHandle.h"



MayhemObjectHandle::MayhemObjectHandle(MayhemObjects* mayhemObjects, unsigned _int32 handleIndex) :
	m_mayhemObjects(mayhemObjects), m_handleIndex(handleIndex)
{
	m_uniqueId = m_mayhemObjects->m_uniqueId[m_handleIndex];
	std::cout << m_uniqueId << std::endl;
}

MayhemObjectHandle::~MayhemObjectHandle()
{
}

// Checks if the object exists
bool MayhemObjectHandle::ObjectExists() const {
	return m_mayhemObjects->m_uniqueId[m_handleIndex] == m_uniqueId;
}

///////////////////////////// Setters ///////////////////////////////////////
bool MayhemObjectHandle::SetTextureLoc(const _int32 textureLoc) {
	if (ObjectExists()) {
		m_mayhemObjects->m_textureLoc[m_handleIndex] = textureLoc;
		return true;
	}
	return false;
}

bool MayhemObjectHandle::SetEnabled(const bool enabled) {
	if (ObjectExists()) {
		m_mayhemObjects->m_enabled[m_handleIndex] = enabled;
		return true;
	}
	return false;
}

bool MayhemObjectHandle::SetPosition(const glm::vec3 pos) {
	if (ObjectExists()) {
		m_mayhemObjects->m_pos[m_handleIndex] = pos;
		return true;
	}
	return false;
}

bool MayhemObjectHandle::SetRotation(const glm::quat rot) {
	if (ObjectExists()) {
		m_mayhemObjects->m_rotation[m_handleIndex] = rot;
		return true;
	}
	return false;
}

bool MayhemObjectHandle::SetRenderableComponent(const Renderable renderable) {
	if (ObjectExists()) {
		m_mayhemObjects->m_renderable[m_handleIndex] = renderable;
		return true;
	}
	return false;
}

///////////////////// Getters ///////////////////////////////////////////////////
_int32 MayhemObjectHandle::GetTextureLoc()const {
	return m_mayhemObjects->m_textureLoc[m_handleIndex];
}

bool MayhemObjectHandle::IsEnabled() const {
	return m_mayhemObjects->m_enabled[m_handleIndex];
}

glm::vec3 MayhemObjectHandle::GetPosition() const {
	return m_mayhemObjects->m_pos[m_handleIndex];
}

glm::quat MayhemObjectHandle::GetRotation() const {
	return m_mayhemObjects->m_rotation[m_handleIndex];
}

Renderable MayhemObjectHandle::GetRenderableComponent() const {
	return m_mayhemObjects->m_renderable[m_handleIndex];
}