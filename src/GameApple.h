#pragma once

#include <GameBoard.h>
#include <libs.h>
#include <models/ModelBase.h>

class GameApple {
  public:
	GameApple();
	~GameApple();

  public:
	void reset(GameBoard *board);
	void tick(GLFWwindow *window, float deltaTime);
	void draw(GLFWwindow *window, glm::mat4 P, glm::mat4 V);

  private:
	ModelBase *model;
	glm::vec3 pos{0.0f, -0.5f, 0.0f};
};
