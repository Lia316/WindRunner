#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Entity.h"

Entity::Entity(float x, float y, float width, float height, float speed)
: x(x), y(y), width(width), height(height), speed(speed) { }

void Entity::move() {
	x += speed;
}

void Entity::draw() {
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glPopMatrix();
}

void Entity::reshape(float _x, float _y, float _w, float _h) {
	x = _x;
	y = _y;
	width = _w;
	height = _h;
}

float Entity::getPositionX() {
	return x;
}

float Entity::getPositionY() {
	return y;
}

float Entity::getWidth() {
	return width;
}

float Entity::getHeight() {
	return height;
}
