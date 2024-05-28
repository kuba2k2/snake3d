#pragma once

#include <GameSnake.h>
#include <GameBoard.h>
#include <libs.h>
#include <models/ModelApple.h>

enum class GameState {
	MENU,
	PLAYING,
	PAUSED,
	OVER,
};

class GameClass {
  public:
	GameClass();
	~GameClass();

  public:
	void newGame();
	void endGame(bool lost = false);
	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	void setViewport(GLFWwindow *window, int width, int height);
	void tick(GLFWwindow *window, float deltaTime);
	void draw(GLFWwindow *window);
	void drawMenu(GLFWwindow *window);

  public:
	bool debug{false};
	GameState state{GameState::MENU};
	GameBoard *board{nullptr};
	GameSnake *snake{nullptr};
	ModelApple *apple;
	int points{0};

  private:
	float windowWidth{0.0f};
	float windowHeight{0.0f};
};

extern GameClass game;
