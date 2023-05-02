#include "Mush.h"

Mush::Mush(Model* model)
	: Entity(glutGet(GLUT_WINDOW_WIDTH), 400, 0, -4.5, model) { }

void Mush::draw() {
	glColor3f(2.0, 0.55, 0.0);
	Entity::draw();
}

void Mush::setY(float posY) {
	y = posY;
}

void Mush::reverse() {//reverse direction
	if (this->speed < -3.5)
		this->speed = -2.5;
	else
		this->speed = -4.5;
}
