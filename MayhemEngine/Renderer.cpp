#include "Renderer.h"



Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Update(double dt) 
{

}

void Renderer::RenderDefault(const DefaultObjectHandle* handle, Shader* shader) 
{
	shader->SetMat4("model", handle->GetTransform());

	std::vector<Mesh>* meshes = handle->GetMeshes();
	for (unsigned int i = 0; i < meshes->size(); i++)
	{
		meshes->at(i).Draw(shader);
	}
}

void Renderer::RenderSkybox(const SkyboxObjectHandle* handle, Shader* shader)
{
	std::vector<Mesh>* meshes = handle->GetMeshes();
	for (unsigned int i = 0; i < meshes->size(); i++)
	{
		meshes->at(i).DrawSkybox(shader);
	}
}

void Renderer::RenderPointLight(const PointLightObjectHandle* handle, const unsigned _int32 index, Shader* shader)
{
	shader->SetVec3(MGH::sprintf("pointLights[%d].position", index), handle->GetPosition());
	shader->SetVec3(MGH::sprintf("pointLights[%d].ambient", index), handle->GetAmbient());
	shader->SetVec3(MGH::sprintf("pointLights[%d].diffuse", index), handle->GetDiffuse());
	shader->SetVec3(MGH::sprintf("pointLights[%d].specular", index), handle->GetSpecular());
	shader->SetFloat(MGH::sprintf("pointLights[%d].constant", index), handle->GetConstant());
	shader->SetFloat(MGH::sprintf("pointLights[%d].linear", index), handle->GetLinear());
	shader->SetFloat(MGH::sprintf("pointLights[%d].quadratic", index), handle->GetQuadratic());
}

void Renderer::RenderDirectionLight(const DirectionLightObjectHandle* handle, const unsigned _int32 index, Shader* shader)
{
	shader->SetVec3(MGH::sprintf("directionLights[%d].direction", index), handle->GetDirection());
	shader->SetVec3(MGH::sprintf("directionLights[%d].ambient", index), handle->GetAmbient());
	shader->SetVec3(MGH::sprintf("directionLights[%d].diffuse", index), handle->GetDiffuse());
	shader->SetVec3(MGH::sprintf("directionLights[%d].specular", index), handle->GetSpecular());
}

void Renderer::RenderSpotLight(const SpotLightObjectHandle* handle, const unsigned _int32 index, Shader* shader)
{
	shader->SetVec3(MGH::sprintf("spotLights[%d].position", index), handle->GetPosition());
	shader->SetVec3(MGH::sprintf("spotLights[%d].direction", index), handle->GetDirection());
	shader->SetVec3(MGH::sprintf("spotLights[%d].ambient", index), handle->GetAmbient());
	shader->SetVec3(MGH::sprintf("spotLights[%d].diffuse", index), handle->GetDiffuse());
	shader->SetVec3(MGH::sprintf("spotLights[%d].specular", index), handle->GetSpecular());
	shader->SetFloat(MGH::sprintf("spotLights[%d].cutOff", index), glm::cos(glm::radians(handle->GetCutOff())));
	shader->SetFloat(MGH::sprintf("spotLights[%d].outerCutOff", index), glm::cos(glm::radians(handle->GetOuterCutOff())));
	shader->SetFloat(MGH::sprintf("spotLights[%d].constant", index), handle->GetConstant());
	shader->SetFloat(MGH::sprintf("spotLights[%d].linear", index), handle->GetLinear());
	shader->SetFloat(MGH::sprintf("spotLights[%d].quadratic", index), handle->GetQuadratic());
}


void Renderer::SetPosition(glm::vec3* position)
{
	//m_transform = glm::translate(m_transform, *position);
	//m_transform = glm::scale(m_transform, glm::vec3(0.2f, 0.2f, 0.2f));
}

void Renderer::Draw()
{
	
}

void Renderer::LoadModel(MayhemObjectHandle* handle, std::string path)
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}

	handle->SetDirectory(path.substr(0, path.find_last_of('/')));

	ProcessNode(handle, scene->mRootNode, scene);
}

unsigned int Renderer::LoadCubeMap(MayhemObjectHandle*, std::vector<std::string> faces)
{
	unsigned int textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, channels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

void Renderer::ProcessNode(MayhemObjectHandle* handle, aiNode *node, const aiScene *scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		handle->GetMeshes()->push_back(ProcessMesh(handle, mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(handle, node->mChildren[i], scene);
	}
}

Mesh Renderer::ProcessMesh(MayhemObjectHandle* handle, aiMesh *mesh, const aiScene *scene)
{

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
						  // positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		// normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;
		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		// tangent
//		vector.x = mesh->mTangents[i].x;
//		vector.y = mesh->mTangents[i].y;
//		vector.z = mesh->mTangents[i].z;
//		vertex.Tangent = vector;
		// bitangent
//		vector.x = mesh->mBitangents[i].x;
//		vector.y = mesh->mBitangents[i].y;
//		vector.z = mesh->mBitangents[i].z;
//		vertex.Bitangent = vector;
		vertices.push_back(vertex);
	}
	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. diffuse maps
	std::vector<Texture> diffuseMaps = LoadMaterialTextures(handle, material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	std::vector<Texture> specularMaps = LoadMaterialTextures(handle, material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<Texture> normalMaps = LoadMaterialTextures(handle, material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<Texture> heightMaps = LoadMaterialTextures(handle, material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Renderer::LoadMaterialTextures(MayhemObjectHandle* handle, aiMaterial *mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		std::vector<Texture>* texturesLoaded = handle->GetTextures();

		for (unsigned int j = 0; j < texturesLoaded->size(); j++)
		{
			if (std::strcmp(texturesLoaded->at(j).path.data(), str.C_Str()) == 0)
			{
				textures.push_back(texturesLoaded->at(j));
				skip = true;
				break;
			}
		}
		if (!skip)
		{   // if texture hasn't been loaded already, load it
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), handle->GetDirectory());
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			texturesLoaded->push_back(texture); // add to loaded textures
		}
	}
	return textures;
}

unsigned int Renderer::TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
