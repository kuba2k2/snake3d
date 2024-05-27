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
	float speed{10.0f};			 // actual movement speed
	float maxLength{4};			 // actual body length
	float updateInterval{0.02f}; // body path resolution
	float slowdownMax{5.0f};	 // maximum turning slowdown

  private:
	float curLength{0.0f};
	float yaw{0.0f};
	float pitch{0.0f};
	ModelCube model;

  private:
	float updateElapsed{0.0f};
	float slowdown{0.0f};
	float slowdownFactor{0.05f};
	float slowdownSpeedupFactor{3.0f};
	int slowdownCount{0};
};

extern SnakeGame snake;
