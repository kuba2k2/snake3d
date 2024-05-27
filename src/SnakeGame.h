#pragma once

#include <libs.h>

#include <models/ModelCube.h>

class SnakeGame {
  private:
	std::list<glm::vec3> path;
	int length	= 100;
	float yaw	= 0.0f;
	float pitch = 0.0f;
	ModelCube model;

  public:
	void advance(GLFWwindow *window, float deltaTime);
	void draw(GLFWwindow *window, glm::mat4 P, glm::mat4 V);
};
