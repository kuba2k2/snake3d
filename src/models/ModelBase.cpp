#include "ModelBase.h"

#include <GameCamera.h>
#include <shaders.h>

void ModelBase::draw(GLFWwindow *window, ShaderProgramType shader, glm::mat4 P, glm::mat4 V, glm::mat4 M) {
	ShaderProgram *sp;
	switch (shader) {
		case ShaderProgramType::SP_COLORED:
			sp = spColored;
			break;
		case ShaderProgramType::SP_LAMBERT:
			sp = spLambert;
			break;
		case ShaderProgramType::SP_LAMBERT_TEXTURED:
			sp = spLambertTextured;
			break;
		case ShaderProgramType::SP_TBN:
			sp = spTbn;
			break;
		case ShaderProgramType::SP_PHONG:
			sp = spPhong;
			break;
	}
	sp->use();

	M = glm::scale(M, glm::vec3(this->scale, this->scale, this->scale));

	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	switch (shader) {
		case ShaderProgramType::SP_COLORED:
			glEnableVertexAttribArray(sp->a("vertex"));
			glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, this->vertices);
			glEnableVertexAttribArray(sp->a("color"));
			glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, this->colors);
			break;
		case ShaderProgramType::SP_LAMBERT:
			glEnableVertexAttribArray(sp->a("vertex"));
			glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, this->vertices);
			glEnableVertexAttribArray(sp->a("normal"));
			glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, this->normals);
			break;
		case ShaderProgramType::SP_LAMBERT_TEXTURED:
			glEnableVertexAttribArray(sp->a("vertex"));
			glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, this->vertices);
			glEnableVertexAttribArray(sp->a("normal"));
			glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, this->normals);
			glEnableVertexAttribArray(sp->a("texCoord"));
			glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, this->texCoords);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, this->tex);
			glUniform1i(sp->u("tex"), 0);
			break;
		case ShaderProgramType::SP_TBN:
			glEnableVertexAttribArray(sp->a("vertex"));
			glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, this->vertices);
			glEnableVertexAttribArray(sp->a("c1"));
			glVertexAttribPointer(sp->a("c1"), 4, GL_FLOAT, false, 0, this->c1);
			glEnableVertexAttribArray(sp->a("c2"));
			glVertexAttribPointer(sp->a("c2"), 4, GL_FLOAT, false, 0, this->c2);
			glEnableVertexAttribArray(sp->a("c3"));
			glVertexAttribPointer(sp->a("c3"), 4, GL_FLOAT, false, 0, this->c3);
			glEnableVertexAttribArray(sp->a("texCoord0"));
			glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, this->texCoords);
			glUniform3f(sp->u("cameraPos"), camera.pos.x, camera.pos.y, camera.pos.z);
			glUniform2f(sp->u("texRepeat"), this->texRepeat.x, this->texRepeat.y);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, this->tex);
			glUniform1i(sp->u("textureMap0"), 0);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, this->texNormal);
			glUniform1i(sp->u("textureMap1"), 1);
			break;
		case ShaderProgramType::SP_PHONG:
			glUniform4f(sp->u("lp"), camera.pos.x, camera.pos.y, camera.pos.z, 1.0f);
			glEnableVertexAttribArray(sp->a("vertex"));
			glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, this->vertices);
			glEnableVertexAttribArray(sp->a("color"));
			glVertexAttribPointer(sp->a("color"), 4, GL_FLOAT, false, 0, this->colors);
			glEnableVertexAttribArray(sp->a("normal"));
			glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, this->normals);
			break;
	}

	glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);

	switch (shader) {
		case ShaderProgramType::SP_COLORED:
			glDisableVertexAttribArray(sp->a("vertex"));
			glDisableVertexAttribArray(sp->a("color"));
			break;
		case ShaderProgramType::SP_LAMBERT:
			glDisableVertexAttribArray(sp->a("vertex"));
			glDisableVertexAttribArray(sp->a("normal"));
			break;
		case ShaderProgramType::SP_LAMBERT_TEXTURED:
			glDisableVertexAttribArray(sp->a("vertex"));
			glDisableVertexAttribArray(sp->a("normal"));
			glDisableVertexAttribArray(sp->a("texCoord"));
			break;
		case ShaderProgramType::SP_TBN:
			glDisableVertexAttribArray(sp->a("vertex"));
			glDisableVertexAttribArray(sp->a("c1"));
			glDisableVertexAttribArray(sp->a("c2"));
			glDisableVertexAttribArray(sp->a("c3"));
			glDisableVertexAttribArray(sp->a("texCoord0"));
			break;
		case ShaderProgramType::SP_PHONG:
			glDisableVertexAttribArray(sp->a("vertex"));
			glDisableVertexAttribArray(sp->a("color"));
			glDisableVertexAttribArray(sp->a("normal"));
			break;
	}
}
