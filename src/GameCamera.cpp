#include "GameCamera.h"

#include <GameInput.h>

GameCamera::GameCamera() {
	this->updateFront();
}

void GameCamera::updateFront() {
	glm::vec3 direction;
	direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	direction.y = sin(glm::radians(this->pitch));
	direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(direction);
}

void GameCamera::setViewport(GLFWwindow *window, int width, int height) {
	this->aspectRatio = (float)width / (float)height;
}

void GameCamera::update(GLFWwindow *window) {
//	this->yaw += input.yaw;
	this->pitch += input.pitch;

	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

	this->updateFront();

	this->pos += this->front * input.walk;
	//	this->pos += glm::normalize(glm::cross(this->front, this->up)) * input.walk;
}

void GameCamera::drawText(float x, float y, const std::string& text, glm::vec3 color) {
	GLTtext *glt = gltCreateText();
	gltSetText(glt, text.c_str());
	gltBeginDraw();
	gltColor(color.r, color.g, color.b, 1.0f);
	gltDrawText2D(glt, x, y, 1.0f);
	gltEndDraw();
	gltDeleteText(glt);
}

GameCamera camera;
