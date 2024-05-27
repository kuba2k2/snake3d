#include "ModelFloor.h"

int myFloorVertexCount = 6;

float myFloorVertices[] = {
	1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	1.0f,  1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f,  -1.0f, 1.0f,
};

float myFloorColors[] = {
	1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

	1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};
float myFloorC1[] = {
	// Ściana 1
	1.000000f, -0.000000f, 0.000000f, 0.000000f, 1.000000f, -0.000000f, 0.000000f, 0.000000f,
	1.000000f, -0.000000f, 0.000000f, 0.000000f, 1.000000f, -0.000000f, 0.000000f, 0.000000f,
	1.000000f, -0.000000f, 0.000000f, 0.000000f, 1.000000f, -0.000000f, 0.000000f, 0.000000f,
};
float myFloorC2[] = {
	// Ściana 1
	-0.000000f, -1.000000f, -0.000000f, 0.000000f, -0.000000f, -1.000000f, -0.000000f, 0.000000f,
	-0.000000f, -1.000000f, -0.000000f, 0.000000f, -0.000000f, -1.000000f, -0.000000f, 0.000000f,
	-0.000000f, -1.000000f, -0.000000f, 0.000000f, -0.000000f, -1.000000f, -0.000000f, 0.000000f,
};
float myFloorC3[] = {
	// Ściana 1
	0.000000f, 0.000000f,  -1.000000f, 0.000000f, 0.000000f, 0.000000f,	 -1.000000f, 0.000000f,
	0.000000f, 0.000000f,  -1.000000f, 0.000000f, 0.000000f, -0.000000f, -1.000000f, 0.000000f,
	0.000000f, -0.000000f, -1.000000f, 0.000000f, 0.000000f, -0.000000f, -1.000000f, 0.000000f,
};

float myFloorNormals[] = {
	0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,

	0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
};

float myFloorVertexNormals[] = {
	1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 1.0f, -1.0f, 0.0f, -1.0f, -1.0f, -1.0f, 0.0f,

	1.0f, -1.0f, -1.0f, 0.0f, 1.0f,	 1.0f, -1.0f, 0.0f, -1.0f, 1.0f,  -1.0f, 0.0f,
};

float myFloorTexCoords[] = {
	1.0f,
	1.0f,
	0.0f,
	0.0f,
	0.0f,
	1.0f,
	1.0f,
	1.0f,
	1.0f,
	0.0f,
	0.0f,
	0.0f,
};

ModelFloor::ModelFloor() {
	this->vertexCount	= myFloorVertexCount;
	this->vertices		= myFloorVertices;
	this->colors		= myFloorColors;
	this->c1			= myFloorC1;
	this->c2			= myFloorC2;
	this->c3			= myFloorC3;
	this->normals		= myFloorNormals;
	this->vertexNormals = myFloorVertexNormals;
	this->texCoords		= myFloorTexCoords;
	this->scale			= 0.5f;
}
