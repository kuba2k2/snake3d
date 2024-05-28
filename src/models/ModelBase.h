#pragma once

#include <libs.h>

enum class ShaderProgramType {
	SP_COLORED,
	SP_LAMBERT,
	SP_LAMBERT_TEXTURED,
	SP_TBN,
	SP_PHONG,
	SP_SPEC,
};

class ModelBase {
  public:
	//	ModelBase();
	//	~ModelBase();

  public:
	void draw(GLFWwindow *window, ShaderProgramType shader, glm::mat4 P, glm::mat4 V, glm::mat4 M);

  protected:
	int vertexCount;
	float *vertices;
	float *colors;
	float *c1, *c2, *c3;
	float *normals;
	float *vertexNormals;
	float *texCoords;

  public:
	float scale = 1.0f;
	GLuint tex;
	GLuint texNormal;
	GLuint texSpec;
	glm::vec2 texRepeat{1.0f, 1.0f};
	glm::vec3 light{0.0f, 0.0f, 0.0f};
	bool lightCustom = false;
};
