#include "ModelApple.h"

#include <modeldata/myapple.h>

ModelApple::ModelApple() {
	this->vertexCount = myappleVertexCount;
	this->vertices	  = myappleVertices;
	//	this->colors		= myappleColors;
	this->c1	  = myappleC1;
	this->c2	  = myappleC2;
	this->c3	  = myappleC3;
	this->normals = myappleNormals;
	//	this->vertexNormals = myappleVertexNormals;
	this->texCoords = myappleTexCoords;
	this->scale		= 15.0f;
}
