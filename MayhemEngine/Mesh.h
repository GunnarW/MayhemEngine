#pragma once

#include <iostream>
#include <vector>
#include "shader.h"
#include "MayhemGameHelper.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};
struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};


class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Vertex>, std::vector<unsigned int>, std::vector<Texture>);
	Mesh(std::vector<Vertex>, std::vector<Texture>);

	~Mesh();

	virtual void Initialize(std::vector<Vertex>, std::vector<unsigned int>, std::vector<Texture>);
	virtual void Initialize(std::vector<Vertex>, std::vector<Texture>);

	void Draw(Shader*);
	void DrawSkybox(Shader* shader);

private:

protected:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Texture> m_textures;

	unsigned int VAO, VBO, EBO;
};

