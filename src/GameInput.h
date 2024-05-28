#pragma once

#include <libs.h>

class GameInput {
  public:
	void setViewport(GLFWwindow *window, int width, int height);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void tick(GLFWwindow *window, float deltaTime);

  public:
	float keyWalkSensitivity{15.0f};
	float keyAngleSensitivity{120.0f};
	float mouseSensitivity{0.1f};
	float mouseMaxAngle{270.0f};
	float yawKey{0.0f};
	float yawMouse{0.0f};
	float pitch{0.0f};
	float walkX{0.0f};
	float walkY{0.0f};
	float walkZ{0.0f};

  private:
	float windowCenterX{0.0f};
	float windowCenterY{0.0f};
	bool firstMouse{true};
};

extern GameInput input;
