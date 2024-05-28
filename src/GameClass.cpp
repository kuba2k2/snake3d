#include "GameClass.h"

#include <GameBoard.h>
#include <GameCamera.h>
#include <GameSnake.h>
#include <models/ModelTeapot.h>

void GameClass::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (action != GLFW_PRESS)
		return;
	switch (key) {
		case GLFW_KEY_ENTER:
			if (game.state == GameState::PLAYING)
				game.state = GameState::PAUSED;
			else if (game.state == GameState::PAUSED)
				game.state = GameState::PLAYING;
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
			break;

		case GLFW_KEY_Z:
			camera.setMode(CameraMode::FREE_CAM);
			break;

		default:
			break;
	}
}

void GameClass::setViewport(GLFWwindow *window, int width, int height) {
	this->windowWidth  = width;
	this->windowHeight = height;
}

void GameClass::tick(GLFWwindow *window, float deltaTime) {
	if (this->state == GameState::PAUSED)
		return;
	snake.tick(window, deltaTime);
}

void GameClass::draw(GLFWwindow *window) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 V = glm::lookAt(camera.pos, camera.pos + camera.front, camera.up);
	glm::mat4 P = glm::perspective(50.0f * glm::pi<float>() / 180.0f, camera.aspectRatio, 0.01f, 100.0f);

	char msg[128];
	sprintf(
		msg,
		"camera=(%f, %f, %f), yaw=%f*, pitch=%f*",
		camera.pos.x,
		camera.pos.y,
		camera.pos.z,
		camera.yaw,
		camera.pitch
	);
	camera.drawText(0.0f, 0.0f, msg, glm::vec3(0.0f, 1.0f, 1.0f));

	board.draw(window, P, V);
	snake.draw(window, P, V);

	glm::mat4 M = glm::mat4(1.0f);
	ModelBase *model;
	model = new ModelTeapot();
	model->draw(window, ShaderProgramType::SP_LAMBERT, P, V, M);
	delete model;

	if (this->state == GameState::PAUSED) {
		camera.drawText(
			this->windowWidth * 0.5f,
			this->windowHeight * 0.5f,
			"PAUSED",
			glm::vec3(1.0f, 1.0f, 1.0f),
			4.0f,
			true
		);
	}

	glfwSwapBuffers(window);
}

GameClass game;
