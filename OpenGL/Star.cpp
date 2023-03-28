#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Star.h"

Star::Star(float x, float y)
	: Entity(x, y, 30, 30, -3.5) { 
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

int Star::getPoint() {
	return point;
}

//void Star::