#include "Shader.h"
#include "Camera.h"
#include "GameManager.h"

GameManager* gameManager;
GLuint  view; 
GLuint  projection;

Camera* camera;
CameraMode viewMode = SIDE;
float camTime = 0.0f;
bool isCamMoving = false;

void init();
void draw();
void idle();
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
    glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}

void init(void) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1000, 500);
	glutInitWindowPosition(900, 0);
	glutCreateWindow("Wind Runner");
	glewInit();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

    Shader* shader = new Shader("mvp.vert", "main.frag");
    GLuint program = shader->program;
    glUseProgram(program);

	view = glGetUniformLocation(program, "view");
	projection = glGetUniformLocation(program, "projection");

	camera = new Camera();
	gameManager = new GameManager(program);
}

void draw() {
	glClearColor(0.5, 0.5, 0.5, 0.0);

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4 mv = camera->getViewMatrix();
    mat4 pv = camera->getProjectionMatrix();

    glUniformMatrix4fv(view, 1, GL_FALSE, &mv[0][0]);
    glUniformMatrix4fv(projection, 1, GL_FALSE, &pv[0][0]);
	
	gameManager->draw();
	glutSwapBuffers();
}

void idle() {
    if (isCamMoving) {
        camTime += 0.0005;

        if (camTime >= 1) {
            camera->setCameraMode(viewMode);
            camTime = 0;
            isCamMoving = false;
        }
        camera->changeEyePos(viewMode, camTime);
        camera->changeProjection(viewMode, camTime);

        glutPostRedisplay();
    }
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
	switch (key) {
    case 033: // Escape Key
    case 'q': case 'Q':
        exit(EXIT_SUCCESS);
        break;
    case '1':
        viewMode = FRONT;
        isCamMoving = true;
        break;
    case '2':
        viewMode = SIDE;
        isCamMoving = true;
        break;
    case '3':
        viewMode = ORTHO;
        isCamMoving = true;
        break;
    }
	gameManager->keyboard(key, x, y);
}
