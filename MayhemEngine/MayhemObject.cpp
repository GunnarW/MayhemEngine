#include "MayhemObject.h"


std::atomic<unsigned _int32> MayhemObject::s_uniqueId;

MayhemObject::MayhemObject(): m_uniqueId(++s_uniqueId)
{
	std::cout << m_uniqueId << std::endl;

	//m_handleIndex = FindFreeSlotInHandleTable();

	if (m_handleIndex < 0) {
		std::cout << "ERROR Creating Object: Max Objects created" << std::endl;
		return;
	}

}

MayhemObject::~MayhemObject()
{

}

void MayhemObject::LoadTexture(const char* filePath) {

}


void MayhemObject::Update(double dt) {

	if (this->m_isEnabled) {

	}
}

void MayhemObject::SetEnabled(bool enabled) {
	this->m_isEnabled = enabled;
}


void MayhemObject::Render(const glm::mat4 projection, const glm::mat4 view) {

}

void MayhemObject::SetPosition(const glm::vec3 position) {
	m_position = position;
}

glm::mat4 MayhemObject::GetModel() const {
	return m_model;
}

int MayhemObject::FindFreeSlotInHandleTable() {
	/*
	for (unsigned _int32 i = 0; i < MAX_GAME_OBJECTS; i++) {
		if (g_apGameObject[i] == NULL) {
			g_apGameObject[i] = this;
			return i;
		}
	}
	*/
	return -1;
}