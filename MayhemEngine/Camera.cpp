#include "Camera.h"



Camera::Camera()
{
	m_position = glm::vec3(0.0f, 0.0f, 5.0f);

	m_pitch = 0;
	m_yaw = 0;
	m_roll = 0;

	m_moveSpeed = 4.0f;
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
	m_velocity.x = -m_moveSpeed;
}

void Camera::StartMoveRight()
{
	m_velocity.x = m_moveSpeed;
}

void Camera::StartMoveUp()
{
	m_velocity.y = m_moveSpeed;
}

void Camera::StartMoveDown()
{
	m_velocity.y = -m_moveSpeed;
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
	m_position += m_velocity * (float)DT;
}

const glm::vec3 Camera::GetPosition()
{
	return m_position;
}

const float Camera::GetPitch()
{
	return m_pitch;
}

const float Camera::GetYaw()
{
	return m_yaw;
}

const float Camera::GetRoll()
{
	return m_roll;
}