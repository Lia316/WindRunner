#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Ground.h"

Ground::Ground()
	: Entity(0, 0, glutGet(GLUT_WINDOW_WIDTH)*1.5, glutGet(GLUT_WINDOW_HEIGHT) / 4, -3.5) { }

Ground::Ground(float height)
	: Entity(glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_WIDTH) / 2, height, -3.5) { }

void Ground::draw() {
	glColor3f(0.7f, 0.5f, 0.3f);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
	Entity::draw();
}

void Ground::move() {
	Entity::move();
}
