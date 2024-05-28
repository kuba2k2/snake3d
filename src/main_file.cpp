/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE
#define GLT_IMPLEMENTATION

#include "GameCamera.h"
#include "GameClass.h"
#include "GameInput.h"
#include "libs.h"
#include "shaders.h"
#include "textures.h"

// Procedura obsługi błędów
void error_callback(int error, const char *description) {
	fputs(description, stderr);
}

void setViewport(GLFWwindow *window, int width, int height) {
	if (height == 0)
		return;
	glViewport(0, 0, width, height);
	gltViewport(width, height);
	camera.setViewport(window, width, height);
	input.setViewport(window, width, height);
	game.setViewport(window, width, height);
}

void initOpenGLProgram(GLFWwindow *window) {
	//	glClearColor(0x21 / 255.0f, 0x96 / 255.0f, 0xf3 / 255.0f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glfwSetKeyCallback(window, GameClass::keyCallback);
	glfwSetScrollCallback(window, GameInput::scrollCallback);
	glfwSetWindowSizeCallback(window, setViewport);
	gltInit();
	initShaders();
	initTextures();
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	setViewport(window, width, height);
	glfwSetTime(0);
}

void freeOpenGLProgram(GLFWwindow *window) {
	gltTerminate();
	freeShaders();
	freeTextures();
}

int main(void) {
	GLFWwindow *window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}
	window = glfwCreateWindow(1280, 720, "OpenGL", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window);
	float lastTime = 0.0f;
	while (!glfwWindowShouldClose(window)) {
		float currentTime = glfwGetTime();
		float deltaTime	  = currentTime - lastTime;
		lastTime		  = currentTime;

		input.tick(window, deltaTime);
		game.tick(window, deltaTime);
		camera.update(window);
		game.draw(window);

		glfwPollEvents();
	}
	freeOpenGLProgram(window);

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
