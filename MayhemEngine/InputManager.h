#pragma once
#include <GLFW/glfw3.h>
#include "Camera.h"

class InputManager
{
public:
	static InputManager& GetInstance();
	void Initialize(Camera*);
	static void StaticKeyPressedCallback(GLFWwindow*, int, int, int, int);
	void KeyPressedCallback(GLFWwindow*, int, int, int, int);

private:
	InputManager(void)
	{
	}
	InputManager(InputManager const&);

	Camera* m_camera;
};

