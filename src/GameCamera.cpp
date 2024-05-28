#include "GameCamera.h"

#include <GameBoard.h>
#include <GameInput.h>
#include <GameSnake.h>

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
	this->staticPos	  = glm::vec3(0.0f, 35.0f, board.width / 3.0f);
}

void GameCamera::update(GLFWwindow *window) {
	switch (this->mode) {
		case CameraMode::STATIC: {
			this->pos	= this->staticPos;
			this->yaw	= -90.0f;
			this->pitch = -75.0f;
			this->updateFront();
			break;
		}
		case CameraMode::FIRST_PERSON: {
			if (snake.path.empty())
				return;
			this->pos	= snake.path.front() + snake.front * 2.0f;
			this->front = snake.front;
			break;
		}
		case CameraMode::BIRDS_EYE: {
			if (snake.path.empty())
				return;
			this->pitch += input.pitch;
			if (this->pitch < -89.0f)
				this->pitch = -89.0f;
			if (this->pitch > -30.0f)
				this->pitch = -30.0f;
			glm::vec3 center = snake.path.front() + snake.front * 2.0f;
			glm::vec3 direction;
			direction.x	   = cos(glm::radians(snake.yaw)) * cos(glm::radians(this->pitch));
			direction.y	   = sin(glm::radians(this->pitch));
			direction.z	   = sin(glm::radians(snake.yaw)) * cos(glm::radians(this->pitch));
			glm::vec3 back = center - glm::normalize(direction) * 20.0f;
			this->pos	   = back;
			this->front	   = center - this->pos;
			break;
		}
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
