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
	struct ParsedObject object;

	jsonObject.at("renderableType").get_to(object.renderable);
	jsonObject.at("enable").get_to(object.enable);
	jsonObject.at("texture").get_to(object.texture);
	jsonObject.at("objectFile").get_to(object.objectFile);
	jsonObject.at("vertexShader").get_to(object.vertexShader);
	jsonObject.at("fragmentShader").get_to(object.fragmentShader);

	nlohmann::json jsonPosition = jsonObject["position"];

	object.position.x = jsonPosition["x"];
	object.position.y = jsonPosition["y"];
	object.position.z = jsonPosition["z"];

	m_parsedObjects.push_back(object);
}