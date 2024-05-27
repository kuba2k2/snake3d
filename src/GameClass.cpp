#include "GameClass.h"

#include <GameCamera.h>

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
					camera.setMode(CameraMode::FREE_CAM);
					break;
				case CameraMode::FREE_CAM:
					camera.setMode(CameraMode::STATIC);
					break;
			}
			break;

		default:
			break;
	}
}

GameClass game;
