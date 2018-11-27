#include "Light.h"


Light::Light()
{

}

Light::Light(glm::vec3 position, glm::vec3 color)
{
	m_position = position;
	m_color = color;
}


Light::~Light()
{
}

void Light::SetPosition(const glm::vec3 position)
{
	m_position = position;
}

void Light::SetColor(const glm::vec3 color)
{
	m_color = color;
}

const glm::vec3 Light::GetPosition()
{
	return m_position;
}

const glm::vec3 Light::GetColor()
{
	return m_color;
}