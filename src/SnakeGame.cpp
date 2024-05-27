#include "SnakeGame.h"

#include <GameCamera.h>
#include <GameInput.h>

SnakeGame::SnakeGame() {
	this->updateFront();
}

void SnakeGame::updateFront() {
	glm::vec3 direction;
	direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	direction.y = sin(glm::radians(this->pitch));
	direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(direction);
}

void SnakeGame::tick(GLFWwindow *window, float deltaTime) {
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

void SnakeGame::draw(GLFWwindow *window, glm::mat4 P, glm::mat4 V) {

	char msg[64];
	sprintf(msg, "speed=%f   curLength=%f", this->speed - this->slowdown, this->curLength);
	camera.drawText(0.0f, 0.0f, msg, glm::vec3(0.0f, 1.0f, 1.0f));

	this->model.scale = 0.5f;

	for (auto pos : this->path) {
		glm::mat4 M = glm::mat4(1.0f);
		M			= glm::translate(M, pos);
		this->model.draw(window, ShaderProgramType::SP_LAMBERT, P, V, M);
	}
}

SnakeGame snake;
