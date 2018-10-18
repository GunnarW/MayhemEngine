#include "MayhemObjects.h"


 //MayhemObjects::m_renderable[MAX_GAME_OBJECTS];

MayhemObjects::MayhemObjects(): m_uniqueId() {
	for (unsigned int i = 0; i < MAX_GAME_OBJECTS; i++) {
	//	m_renderable[i]();
	}
}

MayhemObjects::~MayhemObjects() {

}

unsigned _int32 MayhemObjects::CreateObject() {
	// Find empty game object slot
	for (unsigned _int32 i = 0; i < MAX_GAME_OBJECTS; i++) {
		if (m_uniqueId[i] == 0) {
			m_uniqueId[i] = ++s_uniqueId;

			// return item index
			return i;
		}
	}
}