#include "shaders.h"

ShaderProgram *spLambert;
ShaderProgram *spConstant;
ShaderProgram *spColored;
ShaderProgram *spTextured;
ShaderProgram *spLambertTextured;

void initShaders() {
	spLambert		  = new ShaderProgram("shaders/v_lambert.glsl", NULL, "shaders/f_lambert.glsl");
	spConstant		  = new ShaderProgram("shaders/v_constant.glsl", NULL, "shaders/f_constant.glsl");
	spTextured		  = new ShaderProgram("shaders/v_textured.glsl", NULL, "shaders/f_textured.glsl");
	spColored		  = new ShaderProgram("shaders/v_colored.glsl", NULL, "shaders/f_colored.glsl");
	spLambertTextured = new ShaderProgram("shaders/v_lamberttextured.glsl", NULL, "shaders/f_lamberttextured.glsl");
}

void freeShaders() {
	delete spLambert;
	delete spConstant;
	delete spTextured;
	delete spColored;
	delete spLambertTextured;
}