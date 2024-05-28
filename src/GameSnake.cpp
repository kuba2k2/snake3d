#include "GameSnake.h"

#include <GameCamera.h>
#include <GameClass.h>
#include <GameInput.h>
#include <models/ModelSnakeBodySphere.h>
#include <models/ModelSnakeHead.h>
#include <models/ModelSnakeTail.h>
#include <textures.h>

GameSnake::GameSnake() {
	this->updateFront();
	this->modelBody = new ModelSnakeBodySphere();
	this->modelHead = new ModelSnakeHead();
	this->modelTail = new ModelSnakeTail();

	this->modelHead->tex	   = texSnakeHeadColor;
	this->modelBody->tex	   = texSnakeHead;
	this->modelBody->texNormal = texSnakeHeadNormal;
	this->modelTail->tex	   = texSnakeHead;
	this->modelTail->texNormal = texSnakeHeadNormal;
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
	float yawDelta = input.yawKey;
	if (camera.getMode() != CameraMode::FREE_CAM)
		yawDelta += input.yawMouse;

	float totalSpeedup = 0.0f;
	totalSpeedup += game.score * this->scoreSpeedupFactor;
	totalSpeedup += (game.level - 1) * this->levelSpeedupFactor;

	if (yawDelta == 0.0f) {
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
		float slowdownStep = glm::abs(yawDelta) * this->slowdownFactor;
		if (this->slowdown + slowdownStep < this->slowdownMax) {
			this->slowdown += slowdownStep;
			this->slowdownCount += 1;
		}
	}
	this->yaw += yawDelta * (1.0f + totalSpeedup / 4.0f);

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
		this->frontPath.emplace_front(this->front);
		this->yawPath.emplace_front(this->yaw);
	}

	float curSpeed	   = (this->speed - this->slowdown) * (1.0f + totalSpeedup);
	glm::vec3 prevHead = this->path.front();
	glm::vec3 nextHead = prevHead + this->front * curSpeed * deltaTime;
	this->path.emplace_front(nextHead);
	this->frontPath.emplace_front(this->front);
	this->yawPath.emplace_front(this->yaw);

	this->curLength += glm::length(prevHead - nextHead);
	this->boxPos = this->path.front() + this->front * 1.5f;

	while (this->curLength > this->maxLength) {
		glm::vec3 prevTail = this->path.back();
		this->path.pop_back();
		this->frontPath.pop_back();
		this->yawPath.pop_back();
		glm::vec3 nextTail = this->path.back();
		this->curLength -= glm::length(prevTail - nextTail);
	}
}

void GameSnake::draw(GLFWwindow *window, glm::mat4 P, glm::mat4 V) {
	if (this->path.size() < 3)
		return;

	if (game.debug) {
		float totalSpeedup = 1.0f;
		totalSpeedup += game.score * this->scoreSpeedupFactor;
		totalSpeedup += (game.level - 1) * this->levelSpeedupFactor;
		char msg[128];
		sprintf(msg, "speedup=%f", totalSpeedup);
		camera.drawText(0.0f, 40.0f, msg, glm::vec3(0, 255, 255));
	}

	glm::mat4 M = glm::mat4(1.0f);
	for (auto pos : this->path) {
		glm::mat4 MB = glm::translate(M, pos);
		this->modelBody->draw(window, ShaderProgramType::SP_TBN, P, V, MB);
	}

	glm::mat4 MH = glm::translate(M, this->path.front());
	MH			 = glm::scale(MH, glm::vec3(0.9f, 0.9f, 0.9f));
	MH			 = glm::translate(MH, 0.9f * this->front);
	MH			 = glm::translate(MH, glm::vec3(0.0f, -0.3f, 0.0f));
	MH			 = glm::rotate(MH, glm::radians(-this->yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	MH			 = glm::rotate(MH, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	MH			 = glm::rotate(MH, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	MH			 = glm::rotate(MH, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	this->modelHead->draw(window, ShaderProgramType::SP_PHONG, P, V, MH);

	glm::vec3 tailFront = this->frontPath.back();
	float tailYaw		= this->yawPath.back();
	glm::mat4 MT		= glm::translate(M, this->path.back());
	MT					= glm::scale(MT, glm::vec3(0.6, 0.6f, 0.6f));
	MT					= glm::translate(MT, -0.3f * tailFront);
	MT					= glm::translate(MT, glm::vec3(0.0f, -0.05f, 0.07f));
	MT					= glm::rotate(MT, glm::radians(-tailYaw), glm::vec3(0.0f, 1.0f, 0.0f));
	MT					= glm::rotate(MT, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	this->modelTail->draw(window, ShaderProgramType::SP_TBN, P, V, MT);
}

bool GameSnake::hasCollision(glm::vec3 pos2, glm::vec3 size2) {
	for (auto pos : this->path) {
		if (GameClass::hasCollision(pos, this->boxSize, pos2, size2))
			return true;
	}
	return false;
}
