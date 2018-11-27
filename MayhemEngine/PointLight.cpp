#include "PointLight.h"



PointLight::PointLight()
{
	m_lightTag = "pointLight";
}


PointLight::~PointLight()
{
}

const std::string PointLight::GetLightTag()
{
	return m_lightTag;
}

void PointLight::SetShaderProperties(Shader* shader)
{
	std::string tagString = m_lightTag + "s[" + (char)m_index + "].";
	shader->SetVec3(tagString + "position", m_position);
	shader->SetVec3(tagString + "ambient", m_ambient);
	shader->SetVec3(tagString + "diffuse", m_diffuse);
	shader->SetVec3(tagString + "specular", m_specular);
	shader->SetFloat(tagString + "constant", m_constant);
	shader->SetFloat(tagString + "linear", m_linear);
	shader->SetFloat(tagString + "quadratic", m_quadratic);
}