#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class ShaderProgramType {
	SP_COLORED,
	SP_LAMBERT,
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

  protected:
	float scale = 1.0f;
};
