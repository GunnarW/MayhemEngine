#pragma once
#include "Light.h"
#include <glm/glm.hpp>

#include "Shader.h"

class PointLight :
	public Light
{
public:
	PointLight();
	~PointLight();

	virtual const std::string GetLightTag();
	virtual void SetShaderProperties(Shader*);
private:
	int m_index;
	float m_constant;
	float m_linear;
	float m_quadratic;
};

