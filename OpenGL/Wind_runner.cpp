#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Entity.h"
#include "Ground.h"
#include "Hole.h"
#include "Character.h"
#include "Fire.h"
#include "Star.h"

Ground* ground;
Hole* hole;
Character* character;
Fire* fire;
Star* star;

void init();
void draw();
void move(int time);
void reshape(int w, int h);
void holemaker(int time);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Wind Runner");
	init();
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	glutTimerFunc(10, move, 0); // 10
	glutTimerFunc(3000, holemaker, 0);
	glutKeyboardFunc(keyboard); // 키보드 입력
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
	star = new Star();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	ground->draw();
	hole->draw();
	character->draw();
	fire->draw();
	star->draw();
	glutSwapBuffers();
}

void holemaker(int time) {
	hole = new Hole();
	glutTimerFunc(3000, holemaker, 0);
}

void move(int time) {
	hole->move();
	fire->move();
	star->move();
	character->jump();
	glutPostRedisplay();
	glutTimerFunc(10, move, 0);
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
	star->reshape(h);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 32:
		character->setjump();
	}
	glutPostRedisplay();
}