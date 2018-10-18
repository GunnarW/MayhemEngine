#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>


struct ParsedObject {
	std::string renderable;
	glm::vec3 position;
	std::string texture;
	std::string objectFile;
	std::string vertexShader;
	std::string fragmentShader;
	bool enable;
};

class SceneLoader
{
public:
	SceneLoader();
	~SceneLoader();

	void ParseScene();
	void LoadFile(std::string);
	void ParseObjects();
	std::vector<ParsedObject> GetGameObjects();

private:
	void ParseObject(nlohmann::json);
	std::string m_fileName;
	nlohmann::json m_jsonFile;
	std::vector<ParsedObject> m_parsedObjects;
};

