#include "MayhemObjects.h"



MayhemObjects::MayhemObjects(): m_uniqueId() {

}

MayhemObjects::~MayhemObjects() {

}

unsigned _int32 MayhemObjects::CreateObject() {
	// Find empty game object slot
	for (unsigned _int32 i = 0; i < MAX_GAME_OBJECTS; i++) {
		if (m_uniqueId[i] == 0) {
			m_uniqueId[i] = ++s_uniqueId;
			return i;
		}
	}
}