#pragma once
#include "MayhemObjectHandle.h"
class DefaultObjectHandle :
	public MayhemObjectHandle
{
public:
	explicit DefaultObjectHandle(MayhemObjects* mayhemObjects, unsigned _int32 handleIndex) :
		MayhemObjectHandle(mayhemObjects, handleIndex) {}

	~DefaultObjectHandle();

	// Setters
	bool AddMesh(const Mesh);
	bool AddTexture(const Texture);
	bool SetDirectory(const std::string);

	// Getters
	std::vector<Mesh>* GetMeshes() const;
	std::vector<Texture>* GetTextures() const;
	std::string GetDirectory() const;
};

