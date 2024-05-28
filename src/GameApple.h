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
	bool hasCollision(glm::vec3 pos2, glm::vec3 size2);

  public:
	glm::vec3 pos{0.0f, -0.5f, 0.0f};
	glm::vec3 boxSize{1.2f, 2.0f, 1.2f};
	float speed{90.0f};

  private:
	ModelBase *model;
	float angle{0.0f};
};
