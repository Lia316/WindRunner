#include "Fire.h"

Fire::Fire(float x, float y, Model* model, GLuint shaderProgram)
	: Entity(x, y, 0, -10, model, shaderProgram) {

	const char* file[] = { "C:/Users/light/source/repos/textured_mesh/fire_ball/M_ContentWindow_D.bmp" };
	loadTexture(file, 1);
}

void Fire::draw() {
	if (model == nullptr)
		return;

	glColor3f(9.0, 0.0, 0.0);
	Entity::draw();
}
