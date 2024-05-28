#include "GameBoard.h"

#include <GameCamera.h>
#include <models/ModelCube.h>
#include <models/ModelFloor.h>
#include <textures.h>

GameBoard::GameBoard() {
	this->modelSolid = new ModelCube();
	this->modelFloor = new ModelFloor();
	this->modelWall	 = new ModelFloor();
}

GameBoard::~GameBoard() {
	delete this->modelSolid;
	delete this->modelFloor;
	delete this->modelWall;
}

void GameBoard::draw(GLFWwindow *window, glm::mat4 P, glm::mat4 V) {
	glm::mat4 M;
	glm::vec3 offset = glm::vec3(0.0f, -1.5f, 0.0f);

	// floor
	M = glm::translate(glm::mat4(1.0f), offset);
	M = glm::scale(M, glm::vec3(this->length, this->floor, this->width));
	this->modelSolid->draw(window, ShaderProgramType::SP_LAMBERT, P, V, M);

	// wall Z+
	M = glm::translate(glm::mat4(1.0f), offset);
	M = glm::translate(M, glm::vec3(0.0f, this->height / 2.0f, this->width / 2.0f - this->wall / 2.0f));
	M = glm::scale(M, glm::vec3(this->length, this->height, this->wall));
	this->modelSolid->draw(window, ShaderProgramType::SP_LAMBERT, P, V, M);
	// wall Z-
	M = glm::translate(glm::mat4(1.0f), offset);
	M = glm::translate(M, glm::vec3(0.0f, this->height / 2.0f, -(this->width / 2.0f - this->wall / 2.0f)));
	M = glm::scale(M, glm::vec3(this->length, this->height, this->wall));
	this->modelSolid->draw(window, ShaderProgramType::SP_LAMBERT, P, V, M);
	// wall X+
	M = glm::translate(glm::mat4(1.0f), offset);
	M = glm::translate(M, glm::vec3(this->length / 2.0f - this->wall / 2.0f, this->height / 2.0f, 0.0f));
	M = glm::scale(M, glm::vec3(this->wall, this->height, this->width));
	this->modelSolid->draw(window, ShaderProgramType::SP_LAMBERT, P, V, M);
	// wall X-
	M = glm::translate(glm::mat4(1.0f), offset);
	M = glm::translate(M, glm::vec3(-(this->length / 2.0f - this->wall / 2.0f), this->height / 2.0f, 0.0f));
	M = glm::scale(M, glm::vec3(this->wall, this->height, this->width));
	this->modelSolid->draw(window, ShaderProgramType::SP_LAMBERT, P, V, M);

	this->modelFloor->tex		  = planks;
	this->modelFloor->texNormal	  = planksNormal1;
	this->modelFloor->texSpec	  = planksSpec;
	this->modelFloor->light		  = camera.staticPos;
	this->modelFloor->lightCustom = true;
	this->modelWall->tex		  = texBricks2;
	this->modelWall->texNormal	  = texBricks2Normal;

	float magic		= 0.05f;
	float thickness = 10.0f;

	// floor
	M							= glm::translate(glm::mat4(1.0f), offset);
	M							= glm::translate(M, glm::vec3(0.0f, magic, 0.0f));
	M							= glm::rotate(M, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	M							= glm::translate(M, glm::vec3(0.0f, 0.0f, thickness / 2.0f - this->floor / 2.0f));
	M							= glm::scale(M, glm::vec3(this->length, this->width, thickness));
	this->modelFloor->texRepeat = glm::vec2(this->length / 20.0f, this->width / 20.0f);
	this->modelFloor->draw(window, ShaderProgramType::SP_SPEC, P, V, M);

	this->modelWall->texRepeat = glm::vec2(this->length / 5.0f, (this->height + this->floor / 2.0f) / 5.0f);

	// wall Z+ outer
	M = glm::translate(glm::mat4(1.0f), offset);
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, magic));
	M = glm::rotate(M, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(
		M,
		glm::vec3(0.0f, this->height / 2.0f - this->floor / 4.0f, thickness / 2.0f - this->width / 2.0f)
	);
	M = glm::scale(M, glm::vec3(this->length + magic * 2.0f, this->height + this->floor / 2.0f, thickness));
	this->modelWall->draw(window, ShaderProgramType::SP_TBN, P, V, M);
	// wall Z- outer
	M = glm::translate(glm::mat4(1.0f), offset);
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, -magic));
	M = glm::translate(
		M,
		glm::vec3(0.0f, this->height / 2.0f - this->floor / 4.0f, thickness / 2.0f - this->width / 2.0f)
	);
	M = glm::scale(M, glm::vec3(this->length + magic * 2.0f, this->height + this->floor / 2.0f, thickness));
	this->modelWall->draw(window, ShaderProgramType::SP_TBN, P, V, M);

	// wall Z+ inner
	M = glm::translate(glm::mat4(1.0f), offset);
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, -magic));
	M = glm::translate(
		M,
		glm::vec3(0.0f, this->height / 2.0f - this->floor / 4.0f, thickness / 2.0f + this->width / 2.0f - this->wall)
	);
	M = glm::scale(
		M,
		glm::vec3(this->length - this->wall * 2.0f - magic * 2.0f, this->height + this->floor / 2.0f, thickness)
	);
	this->modelWall->draw(window, ShaderProgramType::SP_TBN, P, V, M);
	// wall Z- inner
	M = glm::translate(glm::mat4(1.0f), offset);
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, magic));
	M = glm::rotate(M, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(
		M,
		glm::vec3(0.0f, this->height / 2.0f - this->floor / 4.0f, thickness / 2.0f + this->width / 2.0f - this->wall)
	);
	M = glm::scale(
		M,
		glm::vec3(this->length - this->wall * 2.0f - magic * 2.0f, this->height + this->floor / 2.0f, thickness)
	);
	this->modelWall->draw(window, ShaderProgramType::SP_TBN, P, V, M);

	this->modelWall->texRepeat = glm::vec2(this->width / 5.0f, (this->height + this->floor / 2.0f) / 5.0f);

	// wall X+ outer
	M = glm::translate(glm::mat4(1.0f), offset);
	M = glm::translate(M, glm::vec3(-magic, 0.0f, 0.0f));
	M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(
		M,
		glm::vec3(0.0f, this->height / 2.0f - this->floor / 4.0f, thickness / 2.0f - this->length / 2.0f)
	);
	M = glm::scale(M, glm::vec3(this->width + magic * 2.0f, this->height + this->floor / 2.0f, thickness));
	this->modelWall->draw(window, ShaderProgramType::SP_TBN, P, V, M);
	// wall X- outer
	M = glm::translate(glm::mat4(1.0f), offset);
	M = glm::translate(M, glm::vec3(magic, 0.0f, 0.0f));
	M = glm::rotate(M, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(
		M,
		glm::vec3(0.0f, this->height / 2.0f - this->floor / 4.0f, thickness / 2.0f - this->length / 2.0f)
	);
	M = glm::scale(M, glm::vec3(this->width + magic * 2.0f, this->height + this->floor / 2.0f, thickness));
	this->modelWall->draw(window, ShaderProgramType::SP_TBN, P, V, M);

	// wall X+ inner
	M = glm::translate(glm::mat4(1.0f), offset);
	M = glm::translate(M, glm::vec3(magic, 0.0f, 0.0f));
	M = glm::rotate(M, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(
		M,
		glm::vec3(0.0f, this->height / 2.0f - this->floor / 4.0f, thickness / 2.0f + this->length / 2.0f - this->wall)
	);
	M = glm::scale(
		M,
		glm::vec3(this->width - this->wall * 2.0f - magic * 2.0f, this->height + this->floor / 2.0f, thickness)
	);
	this->modelWall->draw(window, ShaderProgramType::SP_TBN, P, V, M);
	// wall X- inner
	M = glm::translate(glm::mat4(1.0f), offset);
	M = glm::translate(M, glm::vec3(-magic, 0.0f, 0.0f));
	M = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::translate(
		M,
		glm::vec3(0.0f, this->height / 2.0f - this->floor / 4.0f, thickness / 2.0f + this->length / 2.0f - this->wall)
	);
	M = glm::scale(
		M,
		glm::vec3(this->width - this->wall * 2.0f - magic * 2.0f, this->height + this->floor / 2.0f, thickness)
	);
	this->modelWall->draw(window, ShaderProgramType::SP_TBN, P, V, M);
}

GameBoard board;
