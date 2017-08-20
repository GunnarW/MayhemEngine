#pragma once
#include "MayhemObjects.h"
class MayhemObjectHandle
{
public:
	explicit MayhemObjectHandle(MayhemObjects* mayhemObjects, unsigned _int32 handleIndex);

	~MayhemObjectHandle();

	bool ObjectExists() const;

	// Setters
	bool SetTextureLoc(const _int32 textureLoc);
	bool SetEnabled(const bool enabled);
	bool SetPosition(const glm::vec3 pos);
	bool SetRotation(const glm::quat rot);
	bool SetRenderableComponent(const Renderable renderable);

	// Getters
	_int32 GetTextureLoc()const;
	bool IsEnabled() const;
	glm::vec3 GetPosition() const;
	glm::quat GetRotation() const;
	Renderable GetRenderableComponent() const;

private:
	unsigned _int32 m_uniqueId;
	unsigned _int32 m_handleIndex;
	MayhemObjects* m_mayhemObjects;
};

