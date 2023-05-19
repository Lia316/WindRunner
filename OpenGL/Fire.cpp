#include "Fire.h"

Fire::Fire(float x, float y, Model* model, GLuint* shaderProgram)
	: Entity(x, y, 0, -10, model, shaderProgram) {

	const char* file[] = { "textured_mesh/fire_ball/M_ContentWindow_D.bmp",
		 "textured_mesh/fire_ball/M_ContentWindow_N.bmp" ,
		 "textured_mesh/fire_ball/M_ContentWindow_S.bmp" };
	loadTexture(file, 3);
}

void Fire::draw() {
	if (model == nullptr)
		return;

	glColor3f(9.0, 0.0, 0.0);
	Entity::draw();
}
