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
	void setViewport(GLFWwindow *window, int width, int height);
	void tick(GLFWwindow *window, float deltaTime);
	void draw(GLFWwindow *window);

  public:
	GameState state{GameState::PLAYING};

  private:
	float windowWidth{0.0f};
	float windowHeight{0.0f};
};

extern GameClass game;
