#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Entity.h"
#include "Hole.h"
#include "Ground.h"

Ground* ground;
Hole* hole;

void init();
void draw();
void move();
void reshape(int w, int h);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Wind Runner");
	init();
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutIdleFunc(move);
	glutMainLoop();
	return 0;
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	ground = new Ground();
	hole = new Hole();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	ground->draw();
	hole->draw();
	glutSwapBuffers();
}

void move() {
	hole->move();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	ground->reshape();
}
