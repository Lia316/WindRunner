#include "Star.h"

Star::Star(float x, float y, Model* model, GLuint* shaderProgram)
	: Entity(x, y, 0, -3.5, model, shaderProgram) { 
	point = 5;
	const char* file[] = { "textured_mesh/orange.bmp",
		 "textured_mesh/fire_ball/M_ContentWindow_N.bmp" ,
		 "textured_mesh/fire_ball/M_ContentWindow_S.bmp" };
	loadTexture(file, 3);
}

void Star::draw() {
	if (model)
		model->setColor(vec3(1, 1, 0));
	Entity::draw();
}

int Star::getPoint() {
	return point;
}

void Star::upper() {
	y += 100;
}