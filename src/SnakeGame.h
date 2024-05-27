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
	float speed{5.0f};

  private:
	int length{10};
	float yaw{0.0f};
	float pitch{0.0f};
	ModelCube model;
};

extern SnakeGame snake;
