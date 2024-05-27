#include "ModelTeapot.h"

#include <modeldata/myTeapot.h>

ModelTeapot::ModelTeapot() {
	this->vertexCount	= myTeapotVertexCount;
	this->vertices		= myTeapotVertices;
	this->colors		= myTeapotColors;
	this->c1			= myTeapotC1;
	this->c2			= myTeapotC2;
	this->c3			= myTeapotC3;
	this->normals		= myTeapotNormals;
	this->vertexNormals = myTeapotVertexNormals;
	this->texCoords		= myTeapotTexCoords;
}
