#pragma once

#include <libs.h>

enum class GameState {
	MENU,
	PLAYING,
	PAUSED,
	LOST,
};

class GameClass {
  public:
	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

  public:
	GameState state{GameState::PLAYING};
};

extern GameClass game;
