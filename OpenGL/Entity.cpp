#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Entity.h"

Entity::Entity(float x, float y, float z=0, float speed, Model* model)
: x(x), y(y), speed(speed), model(model) { 
	this->z = model->getminZ() + z;
	width = model->getWidth();
	height = model->getHeight();
	depth = model->getDepth();
}

void Entity::move() {
	x += speed;
}

void Entity::draw() {
	glPushMatrix();
		glTranslatef(x, y, 0);
		model->draw();
	glPopMatrix();
}

float Entity::getPositionX() {
	return x;
}

float Entity::getPositionY() {
	return y;
}

float Entity::getPositionZ() {
	return z;
}

float Entity::getWidth() {
	return width;
}

float Entity::getHeight() {
	return height;
}

float Entity::getDepth() {
	return depth;
}

float Entity::getSpeed() {
	return speed;
}