#pragma once

#include <libs.h>

class GameInput {
  public:
	void setViewport(GLFWwindow *window, int width, int height);
	void tick(GLFWwindow *window, float deltaTime);

  public:
	float keyWalkSensitivity{5.0f};
	float keyAngleSensitivity{120.0f};
	float mouseSensitivity{0.1f};
	float yaw{0.0f};
	float pitch{0.0f};
	float walk{0.0f};

  private:
	float windowCenterX{0.0f};
	float windowCenterY{0.0f};
	bool firstMouse{true};
};

extern GameInput input;
