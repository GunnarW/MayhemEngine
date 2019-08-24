#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

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

	void StartRotation();
	void StopRotation();

	void SetMousePos(double xPos, double yPos);

	void Update(double);

	const glm::vec3 GetPosition();
	const glm::vec3 GetDirection();
	const glm::vec3 GetUpDirection();
	const glm::mat4 GetViewMatrix();

private:
	glm::vec3 m_position;
	glm::vec3 m_velocity;

	void CalculateDirections();

	float m_moveSpeed;
	float m_mouseSpeed;

	float m_horizontalAngle;
	float m_verticalAngle;

	bool m_rotating;
	glm::vec2 m_prevMousePos;
	glm::vec2 m_currentMousePos;

	glm::vec3 m_direction;

	glm::vec3 m_upDirection;
	glm::vec3 m_rightDirection;
};

