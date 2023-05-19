#include "Shader.h"
#include "Camera.h"
#include "GameManager.h"

GameManager* gameManager;
Shader* phongShader;
Shader* gouraudShader;
GLuint objectProgram;
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
void changeShading(GLuint program);

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

	gouraudShader = new Shader("gouraud.vert", "gouraud.frag");
	phongShader = new Shader("phong.vert", "phong.frag");

	objectProgram = phongShader->program;

	camera = new Camera();
	gameManager = new GameManager(&objectProgram, &objectProgram);

	glUniform4f(glGetUniformLocation(objectProgram, "lightDirection"), -0.2f, -1.0f, -0.3f, 0.0f);
	glUniform1f(glGetUniformLocation(objectProgram, "shininess"), 32.0f);
}

void draw() {
	glClearColor(0.1, 0.1, 0.1, 0.0);

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4 vp = camera->getProjectionViewMatrix();
	mat4 vm = camera->getViewMatrix();
	mat4 pm = camera->getProjectionMatrix();
	vec3 cp = camera->getPosition();

	GLuint object_view = glGetUniformLocation(objectProgram, "view");
	GLuint object_projection = glGetUniformLocation(objectProgram, "projection");
	GLuint camera_pos = glGetUniformLocation(objectProgram, "viewPos");

	glUniform3fv(camera_pos, 1, &cp[0]);
	glUniformMatrix4fv(object_view, 1, GL_FALSE, &vm[0][0]);
	glUniformMatrix4fv(object_projection, 1, GL_FALSE, &pm[0][0]);
	
	gameManager->draw();
	glutSwapBuffers();
}

void idle() {
    if (isCamMoving) {
        camTime += 0.001;

        if (camTime >= 1) {
            camera->setCameraMode(viewMode);
            camTime = 0;
            isCamMoving = false;
        }
        camera->changeView(viewMode, camTime);

        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 033: // Escape Key
	case 'q': case 'Q':
		exit(EXIT_SUCCESS);
		break;
	case 'p':
		changeShading(phongShader->program);
		break;
	case 'g':
		changeShading(gouraudShader->program);
		break;
	case '1': // animate only when FRONT <-> SIDE
		if (viewMode == ORTHO) {
			viewMode = FRONT;
			camera->changeView(viewMode, 1);
			camera->setCameraMode(viewMode);
			isCamMoving = false;
		}
		else {
			viewMode = FRONT;
			isCamMoving = true;
		}
		break;
	case '2':
		if (viewMode == ORTHO) {
			viewMode = SIDE;
			camera->changeView(viewMode, 1);
			camera->setCameraMode(viewMode);
			isCamMoving = false;
		}
		else {
			viewMode = SIDE;
			isCamMoving = true;
		}
		break;
	case '3':
		viewMode = ORTHO;
		camera->changeView(viewMode, 1);
		camera->setCameraMode(viewMode);
		isCamMoving = false;
		break;
	}
	gameManager->keyboard(key, x, y);
}

void changeShading(GLuint program) {
	objectProgram = program;
	glUseProgram(objectProgram);
	glUniform4f(glGetUniformLocation(objectProgram, "lightDirection"), -0.2f, -1.0f, -0.3f, 0.0f);
	glUniform1f(glGetUniformLocation(objectProgram, "shininess"), 32.0f);
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
