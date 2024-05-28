#pragma once

#include <GameApple.h>
#include <GameBoard.h>
#include <GameSnake.h>
#include <libs.h>

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
	void newGame(GLFWwindow *window);
	void endGame(GLFWwindow *window, bool lost = false);
	static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	void setViewport(GLFWwindow *window, int width, int height);
	void tick(GLFWwindow *window, float deltaTime);
	void draw(GLFWwindow *window);
	void drawMenu(GLFWwindow *window);
	void drawScore(GLFWwindow *window);
	static bool hasCollision(glm::vec3 pos1, glm::vec3 size1, glm::vec3 pos2, glm::vec3 size2);

  public:
	bool debug{false};
	ModelBase *cube;
	GameState state{GameState::MENU};
	GameBoard *board{nullptr};
	GameSnake *snake{nullptr};
	GameApple *apple{nullptr};
	int points{0};
	int level{1};
	float growth{1.0f};
	bool mouseGrab{false};
	std::string overReason = "The game ended.";

  private:
	float windowWidth{0.0f};
	float windowHeight{0.0f};
};

extern GameClass game;
