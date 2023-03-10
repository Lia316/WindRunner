#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Hole.h"

Hole::Hole()
: Entity(glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_WIDTH) / 7, glutGet(GLUT_WINDOW_HEIGHT) / 4, -0.1) { }

void Hole::draw() {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
	Entity::draw();
}

void Hole::move() {
	Entity::move();
}