#pragma once

#include <libs.h>

enum class CameraMode {
	STATIC,
	FIRST_PERSON,
	BIRDS_EYE,
	FREE_CAM,
};

class GameCamera {
  public:
	GameCamera();

  private:
	void clampPitch();
	void updateFront();

  public:
	void setViewport(GLFWwindow *window, int width, int height);
	void reset();
	void update(GLFWwindow *window);
	void drawText(float x, float y, const std::string &text, glm::vec3 color, float size = 1.0f, bool center = false);
	CameraMode getMode();
	void setMode(CameraMode newMode);

  public:
	glm::vec3 pos{0.0f, 15.0f, 3.0f};
	glm::vec3 front;
	glm::vec3 up{0.0f, 1.0f, 0.0f};
	float yaw{-90.0f};
	float pitch{-75.0f};
	float aspectRatio{1.0f};
	float birdsEyeDistance{10.0f};
	glm::vec3 staticPos{0.0f, 30.0f, 0.0f};

  private:
	glm::vec3 walkFront;
	CameraMode mode{CameraMode::BIRDS_EYE};
};

extern GameCamera camera;
