#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "Model.h"

Model* character = new Model("C:/Users/light/source/repos/fireball.obj");

void display() {
	glPushMatrix();
		//glTranslatef(10, 10, 0);
		character->draw();
	glPopMatrix();

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Wind Runner");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1000.0, 0.0, 500.0, -200.0, 200.0);

	glClearColor(0.5, 0.5, 0.5, 0.0);

	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}


/*
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include "GameManager.h"

GameManager* gameManager;

void init();
void draw();
void moveTimer(int time);
void fireTimer(int time);
void starTimer(int time);
void groundTimer(int time);
void mushTimer(int time);
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Wind Runner");
	init();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 500.0, 0.0, 500.0, -20.0, 20.0);

	glClearColor(0.5, 0.5, 0.5, 0.0);

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(draw);

	glutTimerFunc(10, moveTimer, 0);
	glutTimerFunc(FIRETIME, fireTimer, 0);
	glutTimerFunc(STARTIME, starTimer, 0);
	glutTimerFunc(GROUNDTIME, groundTimer, 0);
	glutTimerFunc(GROUNDTIME * 2, mushTimer, 0);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	gameManager = new GameManager();
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	gameManager->draw();
	glutSwapBuffers();
}

void moveTimer(int time) {
	gameManager->move(moveTimer);
	gameManager->characterAnimation(moveTimer);
}

void fireTimer(int time) {
	gameManager->firemaker(fireTimer);
}

void starTimer(int time) {
	gameManager->starmaker(starTimer);
}

void groundTimer(int time) {
	gameManager->groundmaker(groundTimer);
}

void mushTimer(int time) {
	gameManager->mushmaker(mushTimer);
}

void keyboard(unsigned char key, int x, int y) {
	gameManager->keyboard(key, x, y);
}
*/