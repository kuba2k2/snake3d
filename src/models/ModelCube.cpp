#include "ModelCube.h"

#include <modeldata/myCube.h>

ModelCube::ModelCube() {
	this->vertexCount	= myCubeVertexCount;
	this->vertices		= myCubeVertices;
	this->colors		= myCubeColors;
	this->c1			= myCubeC1;
	this->c2			= myCubeC2;
	this->c3			= myCubeC3;
	this->normals		= myCubeNormals;
	this->vertexNormals = myCubeVertexNormals;
	this->texCoords		= myCubeTexCoords;
	this->scale			= 0.5f;
}
