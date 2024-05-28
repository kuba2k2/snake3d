#include "GameApple.h"

#include <GameCamera.h>
#include <GameClass.h>
#include <models/ModelApple.h>
#include <textures.h>

GameApple::GameApple() {
	srand(time(NULL));
	this->model = new ModelApple();

	this->model->tex	   = texApple;
	this->model->texNormal = texAppleNormal;
}

GameApple::~GameApple() {
	delete this->model;
}

void GameApple::reset(GameBoard *board) {
	float xSize = board->length - 5.0f;
	float ySize = board->width - 5.0f;
	this->pos.x = (float)(rand() % (int)(xSize * 100)) / 100.0f - xSize / 2.0f;
	this->pos.z = (float)(rand() % (int)(ySize * 100)) / 100.0f - ySize / 2.0f;
}

void GameApple::tick(GLFWwindow *window, float deltaTime) {
	this->angle += this->speed * deltaTime;
}

void GameApple::draw(GLFWwindow *window, glm::mat4 P, glm::mat4 V) {
	if (game.debug) {
		char msg[128];
		sprintf(msg, "apple=(%f, %f)", this->pos.x, this->pos.z);
		camera.drawText(0.0f, 20.0f, msg, glm::vec3(0, 255, 255));
	}

	glm::mat4 M = glm::mat4(1.0f);
	M			= glm::translate(M, this->pos);
	M			= glm::rotate(M, glm::radians(this->angle), glm::vec3(0.0f, 1.0f, 0.0f));
	this->model->draw(window, ShaderProgramType::SP_PHONG, P, V, M);
}

bool GameApple::hasCollision(glm::vec3 pos2, glm::vec3 size2) {
	return GameClass::hasCollision(this->pos, this->boxSize, pos2, size2);
}
