#pragma once
#include <GLFW/glfw3.h>
#include "Camera.h"

class InputManager
{
public:
	static InputManager& GetInstance();
	void Initialize(Camera*);

	static void StaticKeyPressedCallback(GLFWwindow*, int, int, int, int);
	static void StaticMousePressedCallback(GLFWwindow* window, int button, int action, int mods);
	static void StaticMouseCursorPosCallback(GLFWwindow* window, double xPos, double yPos);

	void KeyPressedCallback(GLFWwindow*, int, int, int, int);
	void MousePressedCallback(GLFWwindow* window, int button, int action, int mods);
	void MouseCursorPosCallback(GLFWwindow* window, double xPos, double yPos);

private:
	InputManager(void)
	{
	}
	InputManager(InputManager const&);

	Camera* m_camera;
};

