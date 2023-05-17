#include "Shader.h"
#include "Camera.h"
#include "GameManager.h"

GameManager* gameManager;
GLuint  object_projection_view;
GLuint  light_projection_view;
GLuint  camera_pos;

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
void setUpLightEffect(Shader* shader);

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

	Shader* lightShader = new Shader("light.vert", "light.frag");
    Shader* objectShader = new Shader("objects.vert", "objects.frag");
	GLuint lightProgram = lightShader->program;
	GLuint objectProgram = objectShader->program;

	object_projection_view = glGetUniformLocation(objectProgram, "projection_view");
	light_projection_view = glGetUniformLocation(lightProgram, "projection_view");
	camera_pos = glGetUniformLocation(objectProgram, "viewPos");

	camera = new Camera();
	gameManager = new GameManager(objectProgram, lightProgram);

	setUpLightEffect(objectShader);
}

void draw() {
	glClearColor(0.1, 0.1, 0.1, 0.0);

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mat4 vp = camera->getProjectionViewMatrix();
	vec3 cp = camera->getPosition();
    glUniformMatrix4fv(object_projection_view, 1, GL_FALSE, &vp[0][0]);
	glUniformMatrix4fv(light_projection_view, 1, GL_FALSE, &vp[0][0]);
	glUniform3fv(camera_pos, 1, &cp[0]);
	
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

void setUpLightEffect(Shader* shader) {
    shader->setFloat("material.shininess", 32.0f);
    // directional light
    shader->setVec3("directLight.direction", -0.2f, -1.0f, -0.3f);
    shader->setVec3("directLight.ambient", 0.2f, 0.2f, 0.2f);
    shader->setVec3("directLight.diffuse", 0.4f, 0.4f, 0.4f); 
    shader->setVec3("directLight.specular", 0.5f, 0.5f, 0.5f);
    // point light
    shader->setVec3("pointLight.ambient", 0.8f, 0.8f, 0.8f);
    shader->setVec3("pointLight.diffuse", 0.3f, 0.3f, 0.3f);
    shader->setVec3("pointLight.specular", 1.0f, 1.0f, 1.0f);
    shader->setFloat("pointLight.constant", 1.0f);
    shader->setFloat("pointLight.linear", 0.0003f); 
    shader->setFloat("pointLight.quadratic", 0.0001f); 
}
