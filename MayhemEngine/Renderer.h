#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <vector>

#include "MayhemObjectHandle.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void InitializeShader(MayhemObjectHandle* handle);
	void Draw();
	void Update(double dt);
	void Render(MayhemObjectHandle* handle, const glm::mat4 projection, const glm::mat4 view, const glm::vec3);

	void SetPosition(glm::vec3*);
	void LoadModel(MayhemObjectHandle*, std::string);

protected:
	void ProcessNode(MayhemObjectHandle* handle, aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(MayhemObjectHandle* handle, aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> LoadMaterialTextures(MayhemObjectHandle* handle, aiMaterial*, aiTextureType, std::string);
	unsigned int TextureFromFile(const char*, const std::string&, bool gamma = false);
};

