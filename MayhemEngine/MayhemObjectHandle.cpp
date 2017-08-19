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

bool MayhemObjectHandle::ObjectExists() const {
	
	return m_mayhemObjects->m_uniqueId[m_handleIndex] == m_uniqueId;
}