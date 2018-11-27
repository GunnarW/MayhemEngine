#pragma once
#include <glm/glm.hpp>
#include <string>

#include "Shader.h"

class Light
{
public:
	Light();
	Light(glm::vec3, glm::vec3);
	~Light();

	void SetPosition(const glm::vec3);
	void SetColor(const glm::vec3);
	virtual void SetShaderProperties(Shader*) = 0;

	const glm::vec3 GetPosition();
	const glm::vec3 GetColor();
	virtual const std::string GetLightTag() = 0;
	
private:

protected:
	glm::vec3 m_position;
	glm::vec3 m_color;
	std::string m_lightTag;

	glm::vec3 m_ambient;
	glm::vec3 m_specular;
	glm::vec3 m_diffuse;
};

