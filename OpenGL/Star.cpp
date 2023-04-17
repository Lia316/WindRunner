#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Star.h"

Star::Star(float x, float y, Model* model)
	: Entity(x, y, 0, -3.5, model) { 
	point = 5;
}

void Star::draw() {
	glColor3f(1.0, 1.0, 0.0);
	Entity::draw();
}

int Star::getPoint() {
	return point;
}

void Star::upper() {
	y += 100;
}