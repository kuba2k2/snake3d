#include "ModelSnake.h"

#include <modeldata/mySnake.h>

ModelSnake::ModelSnake() {
	this->vertexCount = mySnakeVertexCount;
	this->vertices	  = mySnakeVertices;
	//	this->colors		= mySnakeColors;
	this->c1	  = mySnakeC1;
	this->c2	  = mySnakeC2;
	this->c3	  = mySnakeC3;
	this->normals = mySnakeNormals;
	//	this->vertexNormals = mySnakeVertexNormals;
	this->texCoords = mySnakeTexCoords;
}
