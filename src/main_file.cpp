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

#include "camera.h"
#include "constants.h"
#include "libs.h"
#include "shaderprogram.h"
#include "shaders.h"

#include "models/ModelApple.h"
#include "models/ModelCube.h"
#include "models/ModelCylinder.h"
#include "models/ModelFloor.h"
#include "models/ModelSnake.h"
#include "models/ModelTeapot.h"

// Procedura obsługi błędów
void error_callback(int error, const char *description) {
	fputs(description, stderr);
}

GLuint readTexture(const char *filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	// Wczytanie do pamięci komputera
	std::vector<unsigned char> image; // Alokuj wektor do wczytania obrazka
	unsigned width, height;			  // Zmienne do których wczytamy wymiary obrazka
	// Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);

	// Import do pamięci karty graficznej
	glGenTextures(1, &tex);			   // Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); // Uaktywnij uchwyt
	// Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char *)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}

void initOpenGLProgram(GLFWwindow *window) {
	glClearColor(0x21 / 255.0f, 0x96 / 255.0f, 0xf3 / 255.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window, cameraWindowCallback);
	glfwSetKeyCallback(window, cameraKeyCallback);
	//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, cameraMouseCallback);
	initCamera(window);
	initShaders();
	glfwSetTime(0);
}

void freeOpenGLProgram(GLFWwindow *window) {
	freeShaders();
}

void drawScene(GLFWwindow *window, float angle_x, float angle_y) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 V = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glm::mat4 P = glm::perspective(50.0f * PI / 180.0f, cameraAspectRatio, 0.01f, 50.0f);

	glm::mat4 M = glm::mat4(1.0f);
	//	M			= glm::rotate(M, angle_y, glm::vec3(1.0f, 0.0f, 0.0f));
	//	M			= glm::rotate(M, angle_x, glm::vec3(0.0f, 1.0f, 0.0f));

	ModelBase *model;

//	model = new ModelTeapot();
//	model->draw(window, ShaderProgramType::SP_LAMBERT, P, V, M);
//	M = glm::mat4(1.0f);
//	M = glm::translate(M, glm::vec3(1.0f, 0.0f, 0.0f));
//	model->draw(window, ShaderProgramType::SP_COLORED, P, V, M);
//	delete model;
//
//	model = new ModelCube();
//	model->draw(window, ShaderProgramType::SP_LAMBERT, P, V, M);
//	delete model;
//
//	model = new ModelFloor();
//	model->draw(window, ShaderProgramType::SP_LAMBERT, P, V, M);
//	delete model;

	model = new ModelCylinder();
	model->draw(window, ShaderProgramType::SP_LAMBERT, P, V, M);
	delete model;

	glfwSwapBuffers(window);
}

int main(void) {
	GLFWwindow *window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}
	window = glfwCreateWindow(720, 720, "OpenGL", NULL, NULL);
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

		updateCamera(window, deltaTime);
		drawScene(window, 0.0f, 0.0f);

		glfwPollEvents();
	}
	freeOpenGLProgram(window);

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
