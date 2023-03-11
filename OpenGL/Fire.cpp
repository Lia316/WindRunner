#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Fire.h"

Fire::Fire()
	: Entity(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) / 3, 30, 30, -0.3) { }

void Fire::draw() {
	glColor3f(9.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
	Entity::draw();
}

void Fire::move() {
	Entity::move();
}

void Fire::reshape(float h) {
	Entity::reshape(x, h / 3, width, height);
}