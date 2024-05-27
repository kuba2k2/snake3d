#include "SnakeGame.h"

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

	float curSpeed = this->speed - this->slowdown;
	if (this->path.empty()) {
		this->path.emplace_front(0.0f, 0.0f, 0.0f);
	}
	glm::vec3 prevHeadPos = this->path.front();
	glm::vec3 nextHeadPos = prevHeadPos + this->front * curSpeed * deltaTime;
	this->path.emplace_front(nextHeadPos);
	while (this->path.size() > this->length) {
		this->path.pop_back();
	}
}

void SnakeGame::draw(GLFWwindow *window, glm::mat4 P, glm::mat4 V) {
	this->model.scale = 0.5f;

	for (auto pos : this->path) {
		glm::mat4 M = glm::mat4(1.0f);
		M			= glm::translate(M, pos);
		this->model.draw(window, ShaderProgramType::SP_LAMBERT, P, V, M);
	}
}

SnakeGame snake;
