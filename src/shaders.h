#pragma once

#include "shaderprogram.h"

extern ShaderProgram *spConstant;
extern ShaderProgram *spLambert;
extern ShaderProgram *spTextured;
extern ShaderProgram *spColored;
extern ShaderProgram *spLambertTextured;
extern ShaderProgram *spTbn;
extern ShaderProgram *spPhong;
extern ShaderProgram *spSpec;

void initShaders();
void freeShaders();
