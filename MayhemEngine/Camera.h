#pragma once

#include <glm/glm.hpp>


class Camera
{
public:
	Camera();
	~Camera();

	void StartMoveForward();
	void StartMoveLeft();
	void StartMoveRight();
	void StartMoveBackward();
	void StartMoveUp();
	void StartMoveDown();

	void StopMoveForward();
	void StopMoveLeft();
	void StopMoveRight();
	void StopMoveBackward();
	void StopMoveUp();
	void StopMoveDown();

	void Update(double);

	const glm::vec3 GetPosition();
	const float GetPitch();
	const float GetYaw();
	const float GetRoll();

private:
	glm::vec3 m_position;
	glm::vec3 m_velocity;

	float m_moveSpeed;
	float m_pitch;
	float m_yaw;
	float m_roll;
};

