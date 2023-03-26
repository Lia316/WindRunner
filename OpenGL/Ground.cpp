#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Ground.h"

Ground::Ground()
	: Entity(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) / 4, 0) { }

void Ground::draw() {
	glColor3f(0.7f, 0.5f, 0.3f);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

void Ground::move() {
	Entity::move();
}
