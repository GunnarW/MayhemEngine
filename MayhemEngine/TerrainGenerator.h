#pragma once
#include "TerrainObjectHandle.h"
#include "Mesh.h"
#include "Renderer.h"
#include "stb_image.h"

class TerrainGenerator
{
public:
	TerrainGenerator();
	~TerrainGenerator();

	void ConstructMesh(TerrainObjectHandle *object, Renderer* renderer);
	float ReadHeightMap(uint8_t* image, int x, int y, unsigned int vertexCount, int imgW, int imgH, int maxHeight, int channels);
	glm::vec3 TerrainGenerator::CalculateNormal(uint8_t* image, int x, int y, unsigned int vertexCount, int imgW, int imgH, int maxHeight, int channels);
};

