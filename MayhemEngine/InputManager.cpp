#include "InputManager.h"

#include <iostream>

InputManager& InputManager::GetInstance()
{
	static InputManager instance;
	return instance;
}

void InputManager::Initialize(Camera* camera)
{
	m_camera = camera;
}

void InputManager::StaticKeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GetInstance().KeyPressedCallback(window, key, scancode, action, mods);
}

void InputManager::StaticMousePressedCallback(GLFWwindow* window, int button, int action, int mods)
{
	GetInstance().MousePressedCallback(window, button, action, mods);

}

void InputManager::StaticMouseCursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{
	GetInstance().MouseCursorPosCallback(window, xPos, yPos);

}

void InputManager::MousePressedCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS)
	{
		m_camera->StartRotation();
	}

	if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_RELEASE)
	{
		m_camera->StopRotation();
	}
}

void InputManager::MouseCursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{
	m_camera->SetMousePos(xPos, yPos);
}

void InputManager::KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
		if (key == GLFW_KEY_W && action == GLFW_PRESS)
		{
			m_camera->StartMoveForward();
		}
	
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{
			m_camera->StartMoveBackward();
		}
	
		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
			m_camera->StartMoveLeft();
		}
	
		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
			m_camera->StartMoveRight();
		}

		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		{
			m_camera->StartMoveUp();
		}

		if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
		{
			m_camera->StartMoveDown();
		}

		if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		{
			m_camera->StopMoveForward();
		}

		if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		{
			m_camera->StopMoveBackward();
		}

		if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		{
			m_camera->StopMoveLeft();
		}

		if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		{
			m_camera->StopMoveRight();
		}

		if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
		{
			m_camera->StopMoveUp();
		}

		if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE)
		{
			m_camera->StopMoveDown();
		}
}