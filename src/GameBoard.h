#pragma once

#include <libs.h>

#include <models/ModelBase.h>

class GameBoard {
  public:
	GameBoard();
	~GameBoard();

  public:
	void draw(GLFWwindow *window, glm::mat4 P, glm::mat4 V);
	bool hasCollision(glm::vec3 pos2, glm::vec3 size2);

  public:
	float length{50.0f};
	float width{30.0f};
	float height{5.0f};
	float wall{0.2f};
	float floor{1.0f};

  private:
	ModelBase *modelSolid;
	ModelBase *modelFloor;
	ModelBase *modelWall;
};
