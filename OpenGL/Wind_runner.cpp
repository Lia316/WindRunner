#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "GameManager.h"

GameManager* gameManager;

void init();
void draw();
void moveTimer(int time);
void holeTimer(int time);
void fireTimer(int time);
void starTimer(int time);
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
	glutTimerFunc(1300, fireTimer, 0);
	glutTimerFunc(3000, holeTimer, 0);
	glutTimerFunc(1000, starTimer, 0);

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

void holeTimer(int time) {
	gameManager->holemaker(holeTimer);
}

void fireTimer(int time) {
	gameManager->firemaker(fireTimer);
}

void starTimer(int time) {
	gameManager->starmaker(starTimer);
}

void keyboard(unsigned char key, int x, int y) {
	gameManager->keyboard(key, x, y);
}