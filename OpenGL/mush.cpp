#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Mush.h"

Mush::Mush()
	: Entity(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) / 4, 30,30, -3.5) { }

void Mush::draw() {
	glColor3f(2.0, 0.55, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x + width / 3, y + height / 2);
	glVertex2f(x + width / 3, y);
	glVertex2f(x + width * 2 / 3, y);
	glVertex2f(x + width * 2 / 3, y + height / 2);
	glVertex2f(x + width, y + height / 2);
	glVertex2f(x + width * 2 / 3, y + height);
	glVertex2f(x + width / 3, y + height);
	glVertex2f(x, y + height / 2);
	glEnd();
	Entity::draw();
}

void Mush::move() {
	Entity::move();
}
