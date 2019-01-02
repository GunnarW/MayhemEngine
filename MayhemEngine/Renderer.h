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
#include "DefaultObjectHandle.h"
#include "PointLightObjectHandle.h"
#include "DirectionLightObjectHandle.h"
#include "SpotLightObjectHandle.h"

#include "Shader.h"
#include "MayhemGameHelper.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Draw();
	void Update(double dt);
	void RenderDefault(const DefaultObjectHandle* handle, Shader* shader);
	void RenderPointLight(const PointLightObjectHandle* handle, const unsigned _int32 index, Shader* shader);
	void RenderDirectionLight(const DirectionLightObjectHandle* handle, const unsigned _int32 index, Shader* shader);
	void RenderSpotLight(const SpotLightObjectHandle* handle, const unsigned _int32 index, Shader* shader);
	void SetPosition(glm::vec3*);
	void LoadModel(MayhemObjectHandle*, std::string);
	unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

protected:
	void ProcessNode(MayhemObjectHandle* handle, aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(MayhemObjectHandle* handle, aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> LoadMaterialTextures(MayhemObjectHandle* handle, aiMaterial*, aiTextureType, std::string);
};

