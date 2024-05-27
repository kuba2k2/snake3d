#pragma once

#include <libs.h>

extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;

extern float cameraSensitivity;
extern float cameraSpeed;
extern float cameraAspectRatio;

void initCamera(GLFWwindow *window);
void cameraKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void cameraWindowCallback(GLFWwindow *window, int width, int height);
void cameraMouseCallback(GLFWwindow *window, double xpos, double ypos);
void updateCamera(GLFWwindow *window, float deltaTime);
