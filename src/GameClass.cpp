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

void GameClass::newGame() {
	delete this->board;
	delete this->snake;
	delete this->apple;
	this->board = new GameBoard();
	this->snake = new GameSnake();
	this->apple = new GameApple();
	this->apple->reset(this->board);
	this->state = GameState::PLAYING;
	camera.setViewport(nullptr, this->windowWidth, this->windowHeight);
	camera.reset();
	if (camera.getMode() == CameraMode::FREE_CAM)
		camera.setMode(CameraMode::BIRDS_EYE);
}

void GameClass::endGame(bool lost) {
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
}

void GameClass::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (action != GLFW_PRESS)
		return;

	switch (key) {
		case GLFW_KEY_ENTER:
			if (game.state == GameState::MENU) {
				game.newGame();
				game.mouseGrab = true;
			} else if (game.state == GameState::PLAYING) {
				game.state	   = GameState::PAUSED;
				game.mouseGrab = false;
			} else if (game.state == GameState::PAUSED) {
				game.state	   = GameState::PLAYING;
				game.mouseGrab = true;
			}
			break;

		case GLFW_KEY_F2:
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
			game.endGame();
			break;

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
	}

	if (this->board != nullptr) {
		this->board->draw(window, P, V);
	}
	if (this->snake != nullptr) {
		this->snake->draw(window, P, V);
		if (this->debug) {
			glm::mat4 M = glm::scale(glm::translate(glm::mat4(1.0f), this->snake->boxPos), this->snake->boxSize);
			this->cube->draw(window, ShaderProgramType::SP_COLORED, P, V, M);
			for (auto pos : this->snake->path) {
				M = glm::scale(glm::translate(glm::mat4(1.0f), pos), this->snake->boxSize);
				this->cube->draw(window, ShaderProgramType::SP_COLORED, P, V, M);
			}
		}
	}
	if (this->apple != nullptr) {
		this->apple->draw(window, P, V);
		if (this->debug) {
			glm::mat4 M = glm::scale(glm::translate(glm::mat4(1.0f), this->apple->pos), this->apple->boxSize);
			this->cube->draw(window, ShaderProgramType::SP_COLORED, P, V, M);
		}
	}

	switch (this->state) {
		case GameState::MENU:
			this->drawMenu(window);
			break;
		case GameState::PLAYING:
			break;
		case GameState::PAUSED:
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
		case GameState::OVER:
			break;
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
		"5. Press Esc to end the game.",
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

GameClass game;
