#include "ModelCylinder.h"

#include <modeldata/mycylinder.h>

ModelCylinder::ModelCylinder() {
	this->vertexCount = mycylinderVertexCount;
	this->vertices	  = mycylinderVertices;
	//	this->colors		= mycylinderColors;
	this->c1	  = mycylinderC1;
	this->c2	  = mycylinderC2;
	this->c3	  = mycylinderC3;
	this->normals = mycylinderNormals;
	//	this->vertexNormals = mycylinderVertexNormals;
	this->texCoords = mycylinderTexCoords;
}
