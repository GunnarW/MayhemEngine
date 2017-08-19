#pragma once
#include "MayhemObjects.h"
class MayhemObjectHandle
{
public:
	explicit MayhemObjectHandle(MayhemObjects* mayhemObjects, unsigned _int32 handleIndex);

	~MayhemObjectHandle();

	bool ObjectExists() const;

private:
	unsigned _int32 m_uniqueId;
	unsigned _int32 m_handleIndex;
	MayhemObjects* m_mayhemObjects;
};

