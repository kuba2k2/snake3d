#include "SnakeGame.h"

#include <camera.h>

void SnakeGame::advance(GLFWwindow *window, float deltaTime) {
	float snakeMoveSpeed = 8.0f;
	float snakeTurnSpeed = 180.0f;

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		this->yaw -= snakeTurnSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		this->yaw += snakeTurnSpeed * deltaTime;

	glm::vec3 direction;
	direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	direction.y = sin(glm::radians(this->pitch));
	direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	if (this->path.empty()) {
		this->path.emplace_front(0.0f, 0.0f, 0.0f);
	}
	glm::vec3 prevHeadPos = this->path.front();
	glm::vec3 nextHeadPos = prevHeadPos + glm::normalize(direction) * snakeMoveSpeed * deltaTime;
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
