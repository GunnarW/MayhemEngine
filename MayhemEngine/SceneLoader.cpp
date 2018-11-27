#include "SceneLoader.h"



SceneLoader::SceneLoader()
{
}


SceneLoader::~SceneLoader()
{
}

void SceneLoader::ParseScene()
{
	ParseObjects();
}

void SceneLoader::ParseObjects()
{
	std::vector<nlohmann::json> jsonObjects = m_jsonFile["objects"];

	for (int i = 0; i < jsonObjects.size(); i++)
	{
		ParseObject(jsonObjects[i]);
	}
}

void SceneLoader::LoadFile(std::string fileName)
{
	m_fileName = fileName;
	std::fstream fileStream(m_fileName);
	fileStream >> m_jsonFile;
}

std::vector<ParsedObject> SceneLoader::GetGameObjects()
{
	return m_parsedObjects;
}

void SceneLoader::ParseObject(nlohmann::json jsonObject)
{
	std::cout << jsonObject << std::endl;
	struct ParsedObject object;

	object.renderable = LoadString(jsonObject["renderableType"]);
	object.texture = LoadString(jsonObject["texture"]);
	object.objectFile = LoadString(jsonObject["objectFile"]);
	object.enable = LoadBool(jsonObject["enable"]);
	
	object.position = LoadVec3(jsonObject["position"]);
	object.direction = LoadVec3(jsonObject["direction"]);
	object.ambient = LoadVec3(jsonObject["ambient"]);
	object.diffuse = LoadVec3(jsonObject["diffuse"]);
	object.specular = LoadVec3(jsonObject["specular"]);

	object.constant = LoadFloat(jsonObject["constant"]);
	object.linear = LoadFloat(jsonObject["linear"]);
	object.quadratic = LoadFloat(jsonObject["quadratic"]);
	object.cutOff = LoadFloat(jsonObject["cutOff"]);
	object.outerCutOff = LoadFloat(jsonObject["outerCutoff"]);

	m_parsedObjects.push_back(object);
}

glm::vec3 SceneLoader::LoadVec3(nlohmann::json jsonVec3)
{
	if (jsonVec3 != nullptr)
	{
		return glm::vec3(jsonVec3["x"], jsonVec3["y"], jsonVec3["z"]);
	}
}

std::string SceneLoader::LoadString(nlohmann::json jsonString)
{
	if (jsonString != nullptr)
	{
		return jsonString;
	}
}

bool SceneLoader::LoadBool(nlohmann::json jsonBool)
{
	if (jsonBool != nullptr)
	{
		return bool(jsonBool);
	}
}

float SceneLoader::LoadFloat(nlohmann::json jsonFloat)
{
	if (jsonFloat != nullptr)
	{
		return float(jsonFloat);
	}
}