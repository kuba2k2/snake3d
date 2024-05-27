#include "ModelBase.h"

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
	}
}
