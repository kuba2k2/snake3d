#include "GameClass.h"

#include <GameBoard.h>
#include <GameCamera.h>
#include <GameSnake.h>
#include <models/ModelCube.h>
#include <textures.h>

GameClass::GameClass() {
	this->cube = new ModelCube();
}

GameClass::~GameClass() {
	delete this->board;
	delete this->snake;
	delete this->apple;
	delete this->cube;
}

void GameClass::newGame(GLFWwindow *window) {
	delete this->board;
	delete this->snake;
	delete this->apple;
	this->board = new GameBoard();
	this->snake = new GameSnake();
	this->apple = new GameApple();
	this->apple->reset(this->board);
	this->state = GameState::PLAYING;
	this->score = 0;
	this->level = 1;
	camera.setViewport(nullptr, this->windowWidth, this->windowHeight);
	camera.reset();
	if (camera.getMode() == CameraMode::FREE_CAM)
		camera.setMode(CameraMode::BIRDS_EYE);
	this->mouseGrab = true;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void GameClass::endGame(GLFWwindow *window, bool lost) {
	delete this->snake;
	delete this->board;
	delete this->apple;
	this->snake = nullptr;
	this->board = nullptr;
	this->apple = nullptr;
	if (lost)
		this->state = GameState::OVER;
	else
		this->state = GameState::MENU;
	this->mouseGrab = false;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void GameClass::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (action != GLFW_PRESS)
		return;

	switch (key) {
		case GLFW_KEY_ENTER:
			if (game.state == GameState::MENU || game.state == GameState::OVER) {
				game.newGame(window);
				return;
			} else if (game.state == GameState::PLAYING) {
				game.state	   = GameState::PAUSED;
				game.mouseGrab = false;
			} else if (game.state == GameState::PAUSED) {
				game.state	   = GameState::PLAYING;
				game.mouseGrab = true;
			}
			break;

		case GLFW_KEY_F3:
			game.debug = !game.debug;
			break;

		case GLFW_KEY_F5:
			switch (camera.getMode()) {
				case CameraMode::STATIC:
					camera.setMode(CameraMode::FIRST_PERSON);
					break;
				case CameraMode::FIRST_PERSON:
					camera.setMode(CameraMode::BIRDS_EYE);
					break;
				case CameraMode::BIRDS_EYE:
				case CameraMode::FREE_CAM:
					camera.setMode(CameraMode::STATIC);
					break;
			}
			game.mouseGrab = game.state == GameState::PLAYING;
			break;

		case GLFW_KEY_Z:
			if (camera.getMode() == CameraMode::FREE_CAM) {
				camera.setMode(CameraMode::BIRDS_EYE);
				game.mouseGrab = game.state == GameState::PLAYING;
			} else {
				camera.setMode(CameraMode::FREE_CAM);
				game.mouseGrab = true;
			}
			break;

		case GLFW_KEY_ESCAPE:
		case GLFW_KEY_C:
			if (key == GLFW_KEY_C && mods != GLFW_MOD_CONTROL)
				break;
			game.endGame(window);
			return;

		default:
			break;
	}

	glfwSetInputMode(window, GLFW_CURSOR, game.mouseGrab ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void GameClass::setViewport(GLFWwindow *window, int width, int height) {
	this->windowWidth  = width;
	this->windowHeight = height;
}

void GameClass::tick(GLFWwindow *window, float deltaTime) {
	this->fps.push_front(1.0f / deltaTime);
	while (this->fps.size() > 50)
		this->fps.pop_back();
	if (this->snake != nullptr && this->state != GameState::PAUSED)
		this->snake->tick(window, deltaTime);
	if (this->apple != nullptr)
		this->apple->tick(window, deltaTime);
}

void GameClass::draw(GLFWwindow *window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 V = glm::lookAt(camera.pos, camera.pos + camera.front, camera.up);
	glm::mat4 P = glm::perspective(50.0f * glm::pi<float>() / 180.0f, camera.aspectRatio, 0.01f, 100.0f);

	if (this->debug) {
		char msg[128];
		sprintf(
			msg,
			"camera=(%f, %f, %f), yaw=%f, pitch=%f",
			camera.pos.x,
			camera.pos.y,
			camera.pos.z,
			camera.yaw,
			camera.pitch
		);
		camera.drawText(0.0f, 0.0f, msg, glm::vec3(0, 255, 255));
		float fpsSum = 0.0f;
		for (auto x : this->fps) {
			fpsSum += x;
		}
		sprintf(msg, "FPS: %.02f", fpsSum / this->fps.size());
		camera.drawText(0.0f, this->windowHeight - 20.0f, msg, glm::vec3(0, 255, 255));
	}

	bool isGame = this->board != nullptr && this->snake != nullptr && this->apple != nullptr;

	if (isGame && !this->snake->path.empty()) {
		this->board->draw(window, P, V);
		this->snake->draw(window, P, V);
		this->apple->draw(window, P, V);
		if (this->debug) {
			glm::mat4 M = glm::scale(glm::translate(glm::mat4(1.0f), this->snake->boxPos), this->snake->boxSize);
			this->cube->draw(window, ShaderProgramType::SP_COLORED, P, V, M);
			for (auto pos : this->snake->path) {
				M = glm::scale(glm::translate(glm::mat4(1.0f), pos), this->snake->boxSize);
				this->cube->draw(window, ShaderProgramType::SP_COLORED, P, V, M);
			}
			M = glm::scale(glm::translate(glm::mat4(1.0f), this->apple->pos), this->apple->boxSize);
			this->cube->draw(window, ShaderProgramType::SP_COLORED, P, V, M);
		}

		glm::vec3 headPos  = this->snake->boxPos;
		glm::vec3 headSize = this->snake->boxSize;
		if (this->snake->hasCollision(headPos, headSize)) {
			this->overReason = "Your snake bit itself.";
			this->endGame(window, true);
		} else if (this->board->hasCollision(headPos, headSize)) {
			this->overReason = "Your snake hit a wall.";
			this->endGame(window, true);
		} else if (this->apple->hasCollision(headPos, headSize)) {
			this->score += 1;
			if (this->score % 6 == 0)
				this->level += 1;
			this->apple->reset(this->board);
			this->snake->maxLength += this->snake->growFactor;
		}
	}

	switch (this->state) {
		case GameState::MENU:
			this->drawMenu(window);
			break;
		case GameState::PLAYING:
			this->drawScore(window);
			break;
		case GameState::PAUSED:
			this->drawScore(window);
			if (camera.getMode() == CameraMode::FREE_CAM || this->debug)
				break;
			camera.drawText(
				this->windowWidth * 0.5f,
				this->windowHeight * 0.5f,
				"PAUSED",
				glm::vec3(0xAE, 0xFE, 0x01),
				4.0f,
				true
			);
			break;
		case GameState::OVER: {
			camera.drawText(
				this->windowWidth * 0.5f,
				this->windowHeight * 0.3f,
				"GAME OVER",
				glm::vec3(0xFC, 0x41, 0x36),
				6.0f,
				true
			);
			char msg[128];
			sprintf(msg, "You got %d points.", this->score);
			camera.drawText(
				this->windowWidth * 0.5f,
				this->windowHeight * 0.5f,
				this->overReason,
				glm::vec3(0x95, 0x05, 0x02),
				3.0f,
				true
			);
			camera.drawText(
				this->windowWidth * 0.5f,
				this->windowHeight * 0.6f,
				msg,
				glm::vec3(0x95, 0x05, 0x02),
				3.0f,
				true
			);
			camera.drawText(
				this->windowWidth * 0.5f,
				this->windowHeight * 0.8f,
				"Press Enter to continue.",
				glm::vec3(0xFB, 0xBC, 0x05),
				2.0f,
				true
			);
			break;
		}
	}

	glfwSwapBuffers(window);
}

void GameClass::drawMenu(GLFWwindow *window) {
	camera.drawText(
		this->windowWidth * 0.5f,
		this->windowHeight * 0.2f,
		"Snake",
		glm::vec3(0x21, 0x96, 0xf3),
		7.0f,
		true
	);
	camera.drawText(
		this->windowWidth * 0.5f,
		this->windowHeight * 0.6f,
		"1. Move the snake using arrow keys,\n"
		"   WASD or mouse.\n"
		"2. Eat the apples.\n"
		"3. Don't hit the wall, don't bite yourself.\n"
		"4. Press F5 to change camera view.\n"
		"5. Press Esc to end, Enter to pause.",
		glm::vec3(0x4C, 0x5E, 0xF7),
		2.0f,
		true
	);
	camera.drawText(
		this->windowWidth * 0.5f,
		this->windowHeight * 0.8f,
		"Press Enter to start!",
		glm::vec3(0xFB, 0xBC, 0x05),
		3.0f,
		true
	);
}

void GameClass::drawScore(GLFWwindow *window) {
	char msg[128];
	sprintf(msg, "Score: %d", this->score);
	camera.drawText(this->windowWidth * 0.3f, this->windowHeight * 0.05f, msg, glm::vec3(0x23, 0xAA, 0xF2), 2.0f, true);
	sprintf(msg, "Level: %d", this->level);
	camera.drawText(this->windowWidth * 0.7f, this->windowHeight * 0.05f, msg, glm::vec3(0x23, 0xAA, 0xF2), 2.0f, true);
}

bool GameClass::hasCollision(glm::vec3 pos1, glm::vec3 size1, glm::vec3 pos2, glm::vec3 size2) {
	bool collisionX = pos1.x + size1.x >= pos2.x && pos2.x + size2.x >= pos1.x;
	bool collisionZ = pos1.z + size1.z >= pos2.z && pos2.z + size2.z >= pos1.z;
	return collisionX && collisionZ;
}

GameClass game;
