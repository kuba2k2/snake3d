#include "GameInput.h"

#include <GameCamera.h>
#include <GameClass.h>

void GameInput::setViewport(GLFWwindow *window, int width, int height) {
	input.windowCenterX = width / 2.0f;
	input.windowCenterY = height / 2.0f;
}

void GameInput::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
	camera.birdsEyeDistance -= yoffset;
	if (camera.birdsEyeDistance > 30.0f)
		camera.birdsEyeDistance = 30.0f;
	if (camera.birdsEyeDistance < 8.0f)
		camera.birdsEyeDistance = 8.0f;
}

void GameInput::tick(GLFWwindow *window, float deltaTime) {
	this->yawKey   = 0.0;
	this->yawMouse = 0.0;
	this->pitch	   = 0.0;
	this->walkX	   = 0.0;
	this->walkY	   = 0.0;
	this->walkZ	   = 0.0;

	if (camera.getMode() == CameraMode::FREE_CAM) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			this->walkZ += this->keyWalkSensitivity * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			this->walkZ -= this->keyWalkSensitivity * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			this->walkX -= this->keyWalkSensitivity * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			this->walkX += this->keyWalkSensitivity * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			this->walkY += this->keyWalkSensitivity * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			this->walkY -= this->keyWalkSensitivity * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			this->yawKey -= this->keyAngleSensitivity * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			this->yawKey += this->keyAngleSensitivity * deltaTime;
	} else {
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			this->yawKey -= this->keyAngleSensitivity * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			this->yawKey += this->keyAngleSensitivity * deltaTime;
	}

	if (!game.mouseGrab)
		return;

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

	this->yawMouse += deltaX;
	this->pitch += deltaY;
}

GameInput input;
