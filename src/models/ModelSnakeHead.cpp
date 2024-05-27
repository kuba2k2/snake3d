#include "ModelSnakeHead.h"

#include <modeldata/mysnake_head.h>

ModelSnakeHead::ModelSnakeHead() {
	this->vertexCount = mysnake_headVertexCount;
	this->vertices	  = mysnake_headVertices;
	//	this->colors		= mysnake_headColors;
	this->c1	  = mysnake_headC1;
	this->c2	  = mysnake_headC2;
	this->c3	  = mysnake_headC3;
	this->normals = mysnake_headNormals;
	//	this->vertexNormals = mysnake_headVertexNormals;
	this->texCoords = mysnake_headTexCoords;
}
