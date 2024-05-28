#include "ModelSnakeBodySphere.h"

#include <modeldata/mykolo.h>

ModelSnakeBodySphere::ModelSnakeBodySphere() {
	/*this->vertexCount = myballVertexCount;
	this->vertices	  = myballVertices;
	//	this->colors		= myballColors;
	this->c1	  = myballC1;
	this->c2	  = myballC2;
	this->c3	  = myballC3;
	this->normals = myballNormals;
	//	this->vertexNormals = myballVertexNormals;
	this->texCoords = myballTexCoords;
	this->scale		= 0.005f;*/

	/*this->vertexCount = mysphereVertexCount;
	this->vertices	  = mysphereVertices;
	//	this->colors		= mysphereColors;
	this->c1	  = mysphereC1;
	this->c2	  = mysphereC2;
	this->c3	  = mysphereC3;
	this->normals = mysphereNormals;
	//	this->vertexNormals = mysphereVertexNormals;
	this->texCoords = mysphereTexCoords;
	this->scale		= 0.2f;*/

	this->vertexCount = mykoloVertexCount;
	this->vertices	  = mykoloVertices;
	//	this->colors		= mykoloColors;
	this->c1	  = mykoloC1;
	this->c2	  = mykoloC2;
	this->c3	  = mykoloC3;
	this->normals = mykoloNormals;
	//	this->vertexNormals = mykoloVertexNormals;
	this->texCoords = mykoloTexCoords;
	this->scale		= 0.6f;
}
