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
	init();

	glutDisplayFunc(draw);

	glutTimerFunc(10, moveTimer, 0);
	glutTimerFunc(FIRETIME, fireTimer, 0);
	glutTimerFunc(STARTIME, starTimer, 0);
	glutTimerFunc(GROUNDTIME, groundTimer, 0);
	glutTimerFunc(GROUNDTIME * 5, mushTimer, 0);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}

void init(void) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(900, 0);
	glutCreateWindow("Wind Runner");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	gameManager = new GameManager();
}

void draw() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gameManager->viewProjectionMode();

	glClearColor(0.5, 0.5, 0.5, 0.0);

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gameManager->viewLookMode();
	
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
