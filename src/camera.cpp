#include "camera.h"

glm::vec3 cameraPos	  = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp	  = glm::vec3(0.0f, 1.0f, 0.0f);

float cameraSensitivity = 0.1f;
float cameraSpeed		= 1.0f;
float cameraAspectRatio = 1.0f;

static float windowCenterX	   = 0.0f;
static float windowCenterY	   = 0.0f;
static float cameraMoveForward = 0.0f;
static float cameraMoveSides   = 0.0f;
static bool firstMouse = true;

float yaw	= -90.0f;
float pitch = 0.0f;

void initCamera(GLFWwindow *window) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	windowCenterX = width / 2.0f;
	windowCenterY = height / 2.0f;
}

void cameraKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_W:
				cameraMoveForward = 1.0f;
				break;
			case GLFW_KEY_S:
				cameraMoveForward = -1.0f;
				break;
			case GLFW_KEY_D:
				cameraMoveSides = 1.0f;
				break;
			case GLFW_KEY_A:
				cameraMoveSides = -1.0f;
				break;
			default:
				break;
		}
	} else if (action == GLFW_RELEASE) {
		switch (key) {
			case GLFW_KEY_W:
			case GLFW_KEY_S:
				cameraMoveForward = 0.0f;
				break;
			case GLFW_KEY_D:
			case GLFW_KEY_A:
				cameraMoveSides = 0.0f;
				break;
			default:
				break;
		}
	}
}

void cameraWindowCallback(GLFWwindow *window, int width, int height) {
	if (height == 0)
		return;
	cameraAspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);
	windowCenterX = width / 2.0f;
	windowCenterY = height / 2.0f;
}

void cameraMouseCallback(GLFWwindow *window, double xpos, double ypos) {
	double deltaX = (xpos - windowCenterX) * cameraSensitivity;
	double deltaY = -(ypos - windowCenterY) * cameraSensitivity;
	if (firstMouse) {
		deltaX = 0.0f;
		deltaY = 0.0f;
		firstMouse = false;
	}
	glfwSetCursorPos(window, windowCenterX, windowCenterY);

	yaw += deltaX;
	pitch += deltaY;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

void updateCamera(GLFWwindow *window, float deltaTime) {
	cameraPos += cameraFront * cameraSpeed * deltaTime * cameraMoveForward;
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime * cameraMoveSides;
}
