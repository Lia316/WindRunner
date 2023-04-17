#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Ground.h"

Ground::Ground(Model* model)
	: Entity(0, 0, 0, -3.5, model) { }

//Ground::Ground(float height)
//	: Entity(glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_WIDTH) / 2, height, -3.5) { }

void Ground::draw() {
	glColor3f(0.7f, 0.5f, 0.3f);
	Entity::draw();
}
