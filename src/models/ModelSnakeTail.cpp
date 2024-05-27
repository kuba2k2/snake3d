#include "ModelSnakeTail.h"

#include <modeldata/myogn.h>

ModelSnakeTail::ModelSnakeTail() {
	this->vertexCount = myognVertexCount;
	this->vertices	  = myognVertices;
	//	this->colors		= myognColors;
	this->c1	  = myognC1;
	this->c2	  = myognC2;
	this->c3	  = myognC3;
	this->normals = myognNormals;
	//	this->vertexNormals = myognVertexNormals;
	this->texCoords = myognTexCoords;
}
