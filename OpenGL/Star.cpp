#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Star.h"

Star::Star()
	: Entity(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) / 3, 30, 30, -0.2) {
	point = 5;
}

void Star::draw() {
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
	Entity::draw();
}

void Star::move() {
	Entity::move();
}

void Star::reshape(float h) {
	Entity::reshape(x, h / 3, width, height);
}

int Star::getPoint() {
	return 0;
}