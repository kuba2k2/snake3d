#pragma once

#include <libs.h>

#include <models/ModelCube.h>

class SnakeGame {
  public:
	SnakeGame();

  private:
	void updateFront();

  public:
	void tick(GLFWwindow *window, float deltaTime);
	void draw(GLFWwindow *window, glm::mat4 P, glm::mat4 V);

  public:
	std::list<glm::vec3> path;
	glm::vec3 front;
	float speed{10.0f};

  private:
	int length{10};
	float yaw{0.0f};
	float pitch{0.0f};
	ModelCube model;

  private:
	float updateElapsed{0.0f};
	float updateInterval{0.01f};
	float slowdown{0.0f};
	float slowdownFactor{0.05f};
	float slowdownSpeedupFactor{3.0f};
	float slowdownMax{5.0f};
	int slowdownCount{0};
};

extern SnakeGame snake;
