#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Entity.h"
#include "Ground.h"
#include "Hole.h"
#include "Character.h"
#include "fire.h"

Ground* ground;
Hole* hole;
Character* character;
Fire* fire;

void init();
void draw();
void move(int time);
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
	glutTimerFunc(1, move, 0);
	glutMainLoop();
	return 0;
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	ground = new Ground();
	hole = new Hole();
	character = new Character();
	fire = new Fire();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	ground->draw();
	hole->draw();
	character->draw();
	fire->draw();
	glutSwapBuffers();
}

void move(int time) {
	hole->move();
	fire->move();
	glutPostRedisplay();
	glutTimerFunc(1, move, 0);
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	ground->reshape(w, h);
	hole->reshape(h);
	character->reshape(h);
	fire->reshape(h);
}
