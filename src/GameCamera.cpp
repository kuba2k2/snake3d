#include "GameCamera.h"

#include <GameInput.h>

GameCamera::GameCamera() {
	this->updateFront();
}

void GameCamera::clampPitch() {
	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;
}

void GameCamera::updateFront() {
	glm::vec3 direction;
	direction.x		= cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	direction.y		= sin(glm::radians(this->pitch));
	direction.z		= sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front		= glm::normalize(direction);
	direction.x		= cos(glm::radians(this->yaw));
	direction.y		= 0.0f;
	direction.z		= sin(glm::radians(this->yaw));
	this->walkFront = glm::normalize(direction);
}

void GameCamera::setViewport(GLFWwindow *window, int width, int height) {
	this->aspectRatio = (float)width / (float)height;
}

void GameCamera::update(GLFWwindow *window) {
	switch (this->mode) {
		case CameraMode::FREE_CAM: {
			this->yaw += input.yawMouse;
			this->pitch += input.pitch;
			this->clampPitch();
			this->updateFront();
			this->pos += this->walkFront * input.walkZ;
			this->pos += glm::normalize(glm::cross(this->walkFront, this->up)) * input.walkX;
			this->pos += glm::vec3(0.0f, input.walkY, 0.0f);
			break;
		}
	}
}

void GameCamera::drawText(float x, float y, const std::string &text, glm::vec3 color, float size, bool center) {
	GLTtext *glt = gltCreateText();
	gltSetText(glt, text.c_str());
	gltBeginDraw();
	gltColor(color.r, color.g, color.b, 1.0f);
	if (center) {
		gltDrawText2DAligned(glt, x, y, size, GLT_CENTER, GLT_CENTER);
	} else {
		gltDrawText2D(glt, x, y, size);
	}
	gltEndDraw();
	gltDeleteText(glt);
}

CameraMode GameCamera::getMode() {
	return this->mode;
}

void GameCamera::setMode(CameraMode newMode) {
	this->mode = newMode;
}

GameCamera camera;
