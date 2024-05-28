#include "textures.h"

GLuint texBricks1;
GLuint texBricks2;
GLuint texBricks2Normal;
GLuint planks;
GLuint planksNormal1;
GLuint planksNormal2;
GLuint planksNormal3;
GLuint planksSpec;
GLuint texSnakeHeadColor;
GLuint texSnakeHead;
GLuint texSnakeHeadNormal;
GLuint texSnakeSkin;
GLuint texSnakeSkinNormal;
GLuint texSnake;
GLuint texSnakeNormal;

static GLuint readTexture(const char *filename) {
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

void initTextures() {
	texBricks1		   = readTexture("textures/bricks.png");
	texBricks2		   = readTexture("textures/bricks2_diffuse.png");
	texBricks2Normal   = readTexture("textures/bricks2_normal.png");
	planks			   = readTexture("textures/planks.png");
	planksNormal1	   = readTexture("textures/planksNormal.png");
	planksNormal2	   = readTexture("textures/planksNormalDetail.png");
	planksNormal3	   = readTexture("textures/planksNormal2.png");
	planksSpec		   = readTexture("textures/planksSpec.png");
	texSnakeHeadColor  = readTexture("textures/snakeheadnew.png");
	texSnakeHead	   = readTexture("textures/head.png");
	texSnakeHeadNormal = readTexture("textures/headNormal.png");
	texSnakeSkin	   = readTexture("textures/skin.png");
	texSnakeSkinNormal = readTexture("textures/skinNormal.png");
	texSnake		   = readTexture("textures/snake.png");
	texSnakeNormal	   = readTexture("textures/snakeNormal.png");
	glGenerateMipmap(GL_TEXTURE_2D);
}

void freeTextures() {
	glDeleteTextures(1, &texBricks1);
	glDeleteTextures(1, &texBricks2);
	glDeleteTextures(1, &texBricks2Normal);
	glDeleteTextures(1, &planks);
	glDeleteTextures(1, &planksNormal1);
	glDeleteTextures(1, &planksNormal2);
	glDeleteTextures(1, &planksNormal3);
	glDeleteTextures(1, &planksSpec);
	glDeleteTextures(1, &texSnakeHeadColor);
	glDeleteTextures(1, &texSnakeHead);
	glDeleteTextures(1, &texSnakeHeadNormal);
	glDeleteTextures(1, &texSnakeSkin);
	glDeleteTextures(1, &texSnakeSkinNormal);
	glDeleteTextures(1, &texSnake);
	glDeleteTextures(1, &texSnakeNormal);
}
