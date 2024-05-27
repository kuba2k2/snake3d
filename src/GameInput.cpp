#include "GameInput.h"

void GameInput::setViewport(GLFWwindow *window, int width, int height) {
	input.windowCenterX = width / 2.0f;
	input.windowCenterY = height / 2.0f;
}

void GameInput::tick(GLFWwindow *window, float deltaTime) {
	this->yaw	= 0.0;
	this->pitch = 0.0;
	this->walk	= 0.0;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		this->walk += this->keyWalkSensitivity * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		this->walk -= this->keyWalkSensitivity * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		this->yaw -= this->keyAngleSensitivity * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		this->yaw += this->keyAngleSensitivity * deltaTime;

	double mouseX = 0.0, mouseY = 0.0;
	if (this->firstMouse) {
		this->firstMouse = false;
		mouseX			 = this->windowCenterX;
		mouseY			 = this->windowCenterY;
	} else {
		glfwGetCursorPos(window, &mouseX, &mouseY);
	}
	glfwSetCursorPos(window, this->windowCenterX, this->windowCenterY);

	float deltaX = (mouseX - this->windowCenterX) * this->mouseSensitivity;
	float deltaY = -(mouseY - this->windowCenterY) * this->mouseSensitivity;

	deltaX = glm::min(deltaX, this->mouseMaxAngle * deltaTime);
	deltaY = glm::min(deltaY, this->mouseMaxAngle * deltaTime);
	deltaX = glm::max(deltaX, -this->mouseMaxAngle * deltaTime);
	deltaY = glm::max(deltaY, -this->mouseMaxAngle * deltaTime);

	this->yaw += deltaX;
	this->pitch += deltaY;
}

GameInput input;
