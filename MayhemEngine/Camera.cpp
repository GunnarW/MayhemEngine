#include "Camera.h"


Camera::Camera()
{
	m_position = glm::vec3(0.0f, 5.0f, 50.0f);
	

	m_moveSpeed = 130.0f;
	m_mouseSpeed = 0.6f;
	m_rotating = false;

	m_horizontalAngle = 0.0f;
	m_verticalAngle = 0.0f;

	CalculateDirections();
}

Camera::~Camera()
{
}

void Camera::StartMoveForward()
{
	m_velocity.z = -m_moveSpeed;
}

void Camera::StartMoveBackward()
{
	m_velocity.z = m_moveSpeed;
}

void Camera::StartMoveLeft()
{
	m_velocity.x = m_moveSpeed;
}

void Camera::StartMoveRight()
{
	m_velocity.x = -m_moveSpeed;
}

void Camera::StartMoveUp()
{
	m_velocity.y = -m_moveSpeed;
}

void Camera::StartMoveDown()
{
	m_velocity.y = m_moveSpeed;
}


void Camera::StopMoveForward()
{
	m_velocity.z = 0.0;
}

void Camera::StopMoveBackward()
{
	m_velocity.z = 0.0;
}

void Camera::StopMoveLeft()
{
	m_velocity.x = 0.0;
}

void Camera::StopMoveRight()
{
	m_velocity.x = 0.0;
}

void Camera::StopMoveUp()
{
	m_velocity.y = 0.0f;
}

void Camera::StopMoveDown()
{
	m_velocity.y = 0.0f;
}

void Camera::Update(double DT)
{
	// forward/backwards
	m_position +=  m_velocity.z * m_direction * (float)DT;
	// up/down
	m_position += m_velocity.y * m_upDirection * (float)DT;
	// left/right
	m_position += m_velocity.x * m_rightDirection * (float)DT;


	if (m_rotating)
	{
		m_horizontalAngle += m_mouseSpeed * (float)DT * float(m_prevMousePos.x - m_currentMousePos.x);
		m_verticalAngle += m_mouseSpeed * (float)DT * float(m_prevMousePos.y - m_currentMousePos.y);
		CalculateDirections();
	}
}

const glm::vec3 Camera::GetPosition()
{
	return m_position;
}

void Camera::StartRotation()
{
	m_rotating = true;
}

void Camera::StopRotation()
{
	m_rotating = false;
}

void Camera::SetMousePos(double xPos, double yPos)
{
	m_prevMousePos = m_currentMousePos;
	m_currentMousePos = glm::vec2(xPos, yPos);
}

const glm::vec3 Camera::GetDirection()
{
	return m_direction;
}


void Camera::CalculateDirections()
{
	m_direction = glm::vec3(
		cos(m_verticalAngle) * sin(m_horizontalAngle),
		sin(m_verticalAngle),
		cos(m_verticalAngle) * cos(m_horizontalAngle)
	);

	m_rightDirection = glm::vec3(
		sin(m_horizontalAngle - 3.14f / 2.0f),
		0.0f, 
		cos(m_horizontalAngle - 3.14f / 2.0f)
	);

	m_upDirection = glm::cross(m_rightDirection, m_direction);
}

const glm::vec3 Camera::GetUpDirection()
{
	return m_upDirection;
}