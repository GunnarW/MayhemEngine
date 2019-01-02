#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>



struct ParsedObject 
{
	std::string type;

	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	glm::vec2 gridSize;

	std::string texture;
	std::string slopeTexture;
	std::string heightmap;
	std::string objectFile;
	std::string vs;
	std::string fs;
	
	bool enable;

	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
	float altitudeScale;

	int vertexCount;
};

class SceneLoader
{
public:
	SceneLoader();
	~SceneLoader();

	void ParseScene();
	void LoadFile(std::string);
	std::vector<ParsedObject> GetGameObjects();

private:
	void ParseObjects();
	void ParseObject(nlohmann::json);
	
	std::string m_fileName;
	nlohmann::json m_jsonFile;
	std::vector<ParsedObject> m_parsedObjects;

	glm::vec3 LoadVec3(nlohmann::json);
	glm::vec2 LoadVec2(nlohmann::json);
	std::string LoadString(nlohmann::json);
	bool LoadBool(nlohmann::json);
	float LoadFloat(nlohmann::json);

	int LoadInt(nlohmann::json);
};

