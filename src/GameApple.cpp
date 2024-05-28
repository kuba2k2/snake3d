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

void GameApple::tick(GLFWwindow *window, float deltaTime) {}

void GameApple::draw(GLFWwindow *window, glm::mat4 P, glm::mat4 V) {
	if (game.debug) {
		char msg[128];
		sprintf(msg, "apple=(%f, %f)", this->pos.x, this->pos.z);
		camera.drawText(0.0f, 20.0f, msg, glm::vec3(0, 255, 255));
	}

	glm::mat4 M = glm::mat4(1.0f);
	M			= glm::translate(M, this->pos);
	this->model->draw(window, ShaderProgramType::SP_LAMBERT_TEXTURED, P, V, M);
}
