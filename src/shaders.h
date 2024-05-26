#pragma once

#include "shaderprogram.h"

extern ShaderProgram *spConstant;
extern ShaderProgram *spLambert;
extern ShaderProgram *spTextured;
extern ShaderProgram *spColored;
extern ShaderProgram *spLambertTextured;

void initShaders();
void freeShaders();