#include "Star.h"

Star::Star(float x, float y, Model* model, GLuint shaderProgram)
	: Entity(x, y, 0, -3.5, model, shaderProgram) { 
	point = 5;
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