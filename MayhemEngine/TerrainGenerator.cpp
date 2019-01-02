#include "TerrainGenerator.h"

TerrainGenerator::TerrainGenerator()
{
}


TerrainGenerator::~TerrainGenerator()
{
}

void TerrainGenerator::ConstructMesh(TerrainObjectHandle *object, Renderer* renderer)
{
	int vertexCount = object->GetVertexCount();
	glm::vec2 gridSize = object->GetGridSize();
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices(6 * (vertexCount - 1)*(vertexCount - 1), 0);
	std::vector<Texture> textures;

	Texture texture;
	texture.path = object->GetTexturePath(0);
	texture.type = "texture_diffuse";
	texture.id = renderer->TextureFromFile(texture.path.c_str(), "Textures");
	textures.push_back(texture);

	Texture slopeTexture;
	slopeTexture.path = object->GetTexturePath(1);
	slopeTexture.type = "texture_slope";
	slopeTexture.id = renderer->TextureFromFile(slopeTexture.path.c_str(), "Textures");
	textures.push_back(slopeTexture);

	int height, width, channels;
	uint8_t* image = stbi_load(object->GetTexturePath(2).c_str(), &width, &height, &channels, 3);

	for (unsigned int i = 0; i < vertexCount; i++)
	{
		for (unsigned int j = 0; j < vertexCount; j++)
		{
			Vertex vertex;

			vertex.Position = glm::vec3(
				(float)j / ((float)vertexCount - 1) * gridSize.x,
				ReadHeightMap(image, i, j, vertexCount, width, height, object->GetAltitudeScale(), channels),
				(float)i / ((float)vertexCount - 1) * gridSize.y
			);
			vertex.Normal = CalculateNormal(image, i, j, vertexCount, width, height, object->GetAltitudeScale(), channels);
			vertex.TexCoords = glm::vec2(
				(float)j / ((float)vertexCount - 1) * 60,
				(float)i / ((float)vertexCount - 1) * 60
			);
			vertices.push_back(vertex);
		}
	}

	int count = 0;
	for (unsigned int gz = 0; gz < vertexCount - 1; gz++)
	{
		for (unsigned int gx = 0; gx < vertexCount - 1; gx++)
		{
			unsigned int topLeft = (gz * vertexCount) + gx;
			unsigned int topRight = topLeft + 1;
			unsigned int bottomLeft = ((gz + 1) * vertexCount) + gx;
			unsigned int bottomRight = bottomLeft + 1;
			indices[count++] = topLeft;
			indices[count++] = bottomLeft;
			indices[count++] = topRight;
			indices[count++] = topRight;
			indices[count++] = bottomLeft;
			indices[count++] = bottomRight;
		}
	}
	object->GetMeshes()->push_back(Mesh(vertices, indices, textures));
	delete image;
}

float TerrainGenerator::ReadHeightMap(uint8_t* image, int x, int y, unsigned int vertexCount, int imgW, int imgH, int maxHeight, int channels)
{
	int newX = imgW / vertexCount * x;
	int newY = imgH / vertexCount * y;

	unsigned offset = channels * (imgW * newX + newY);

	if (offset > imgW * imgH * channels)
	{
		return 0.0f;
	}

	int maxPixels = 256 * 256 * 256;
	int r = image[offset];
	int g = image[offset + 1];
	int b = image[offset + 2];

	int color = r * g * b;

	float height = (float)color / (float)maxPixels * (float)maxHeight;

	return height;
}

glm::vec3 TerrainGenerator::CalculateNormal(uint8_t* image, int x, int y, unsigned vertexCount, int imgW, int imgH, int maxHeight, int channels)
{
	float heightL = ReadHeightMap(image, x - 1, y, vertexCount, imgW, imgH, maxHeight, channels);
	float heightR = ReadHeightMap(image, x + 1, y, vertexCount, imgW, imgH, maxHeight, channels);
	float heightD = ReadHeightMap(image, x, y - 1, vertexCount, imgW, imgH, maxHeight, channels);
	float heightU = ReadHeightMap(image, x, y + 1, vertexCount, imgW, imgH, maxHeight, channels);

	return glm::normalize(glm::vec3(heightL - heightR, 2.0f, heightD - heightU));
}