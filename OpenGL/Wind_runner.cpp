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
void reshape(int w, int h);
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

	glutTimerFunc(10, moveTimer, 0);
	glutTimerFunc(1300, fireTimer, 0);
	glutTimerFunc(3000, holeTimer, 0);
	glutTimerFunc(500, starTimer, 0);

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
	glClear(GL_COLOR_BUFFER_BIT);
	gameManager->draw();
	glutSwapBuffers();
}

void moveTimer(int time) {
	gameManager->move(moveTimer);
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

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gameManager->reshape(w, h);
}

void keyboard(unsigned char key, int x, int y) {
	gameManager->keyboard(key, x, y);
}