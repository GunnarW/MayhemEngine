#include "MayhemObjectHandle.h"


// creates a reference to object in MayhemObjects
MayhemObjectHandle::MayhemObjectHandle(MayhemObjects* mayhemObjects, unsigned _int32 handleIndex) :
	m_mayhemObjects(mayhemObjects), m_handleIndex(handleIndex)
{
	m_uniqueId = m_mayhemObjects->m_uniqueId[m_handleIndex];
	std::cout << "Unique ID: " << m_uniqueId << std::endl;
}

MayhemObjectHandle::~MayhemObjectHandle()
{
}

// Checks if the object exists
bool MayhemObjectHandle::ObjectExists() const {
	return m_mayhemObjects->m_uniqueId[m_handleIndex] == m_uniqueId;
}

bool MayhemObjectHandle::HasRenderableComponent() const {
	return &m_mayhemObjects->m_renderable[m_handleIndex]  != NULL;
}

///////////////////////////// Setters ///////////////////////////////////////
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

bool MayhemObjectHandle::IsEnabled() const {
	if (ObjectExists()) {
		return m_mayhemObjects->m_enabled[m_handleIndex];
	}
}

glm::vec3 MayhemObjectHandle::GetPosition() const {
	if (ObjectExists()) {
		return m_mayhemObjects->m_pos[m_handleIndex];
	}
}

glm::quat MayhemObjectHandle::GetRotation() const {
	if (ObjectExists()) {
		return m_mayhemObjects->m_rotation[m_handleIndex];
	}
}


Renderable* MayhemObjectHandle::GetRenderableComponent() const {
	if (ObjectExists()) {
	return &m_mayhemObjects->m_renderable[m_handleIndex];
	}
}


