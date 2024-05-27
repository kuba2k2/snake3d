#include "GameSnake.h"

#include <GameCamera.h>
#include <GameInput.h>
#include <models/ModelSnakeBodySphere.h>
#include <models/ModelSnakeHead.h>

GameSnake::GameSnake() {
	this->updateFront();
	this->modelBody = new ModelSnakeBodySphere();
	this->modelHead = new ModelSnakeHead();
}

GameSnake::~GameSnake() {
	delete this->modelBody;
	delete this->modelHead;
	delete this->modelTail;
}

void GameSnake::updateFront() {
	glm::vec3 direction;
	direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	direction.y = sin(glm::radians(this->pitch));
	direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(direction);
}

void GameSnake::tick(GLFWwindow *window, float deltaTime) {
	if (!freeCam)
		this->yaw += input.yaw;
	if (input.yaw == 0.0f) {
		if (this->slowdownCount == 0) {
			this->slowdown = 0.0f;
		} else {
			float speedupStep = this->slowdown / (float)this->slowdownCount;
			speedupStep *= this->slowdownSpeedupFactor;
			if (this->slowdown - speedupStep >= 0.0f) {
				this->slowdown -= speedupStep;
			}
			this->slowdownCount -= 1;
		}
	} else {
		float slowdownStep = glm::abs(input.yaw) * this->slowdownFactor;
		if (this->slowdown + slowdownStep < this->slowdownMax) {
			this->slowdown += slowdownStep;
			this->slowdownCount += 1;
		}
	}

	this->updateElapsed += deltaTime;
	if (this->updateElapsed > this->updateInterval) {
		this->updateElapsed -= this->updateInterval;
		deltaTime = this->updateInterval;
	} else {
		return;
	}

	this->updateFront();

	if (this->path.empty()) {
		this->path.emplace_front(0.0f, 0.0f, 0.0f);
	}

	float curSpeed	   = this->speed - this->slowdown;
	glm::vec3 prevHead = this->path.front();
	glm::vec3 nextHead = prevHead + this->front * curSpeed * deltaTime;
	this->path.emplace_front(nextHead);

	this->curLength += glm::length(prevHead - nextHead);

	while (this->curLength > this->maxLength) {
		glm::vec3 prevTail = this->path.back();
		this->path.pop_back();
		glm::vec3 nextTail = this->path.back();
		this->curLength -= glm::length(prevTail - nextTail);
	}
}

void GameSnake::draw(GLFWwindow *window, glm::mat4 P, glm::mat4 V) {

	char msg[64];
	sprintf(msg, "speed=%f   curLength=%f", this->speed - this->slowdown, this->curLength);
	camera.drawText(0.0f, 0.0f, msg, glm::vec3(0.0f, 1.0f, 1.0f));

	if (this->path.size() < 3)
		return;

	glm::mat4 M = glm::mat4(1.0f);
	for (auto pos : this->path) {
		glm::mat4 MB = glm::translate(M, pos);
		this->modelBody->draw(window, ShaderProgramType::SP_LAMBERT, P, V, MB);
	}

	glm::mat4 MH = glm::translate(M, this->path.front());
	MH			 = glm::scale(MH, glm::vec3(0.9f, 0.9f, 0.9f));
	MH			 = glm::translate(MH, 0.9f * this->front);
	MH			 = glm::rotate(MH, glm::radians(-this->yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	MH			 = glm::rotate(MH, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	MH			 = glm::rotate(MH, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	MH			 = glm::rotate(MH, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	this->modelHead->draw(window, ShaderProgramType::SP_LAMBERT, P, V, MH);

	glm::mat4 MT = glm::translate(M, this->path.back());
}

GameSnake snake;
