#pragma once

#include <libs.h>

class GameCamera {
  public:
	GameCamera();

  private:
	void updateFront();

  public:
	void setViewport(GLFWwindow *window, int width, int height);
	void update(GLFWwindow *window);
	void drawText(float x, float y, const std::string& text, glm::vec3 color);

  public:
	glm::vec3 pos{0.0f, 15.0f, 3.0f};
	glm::vec3 front;
	glm::vec3 up{0.0f, 1.0f, 0.0f};
	float aspectRatio{1.0f};

  private:
	float yaw{-90.0f};
	float pitch{-75.0f};
};

extern GameCamera camera;
