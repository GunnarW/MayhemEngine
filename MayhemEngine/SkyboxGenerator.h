#pragma once
#include "SkyboxObjectHandle.h"
#include "Renderer.h"

class SkyboxGenerator
{
public:
	SkyboxGenerator();
	~SkyboxGenerator();

	void ConstructSkybox(SkyboxObjectHandle* handle, Renderer* renderer);

	 std::vector<Vertex> ConstructMesh();
};

