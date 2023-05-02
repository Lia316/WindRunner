//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "Shader.h"
//#include "Camera.h"
//
//using namespace std;
//using namespace glm;
//
//typedef vec4  color4;
//typedef vec4  point4;
//
//const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)
//
//point4 points[NumVertices];
//color4 colors[NumVertices];
//
//// Vertices of a unit cube centered at origin, sides aligned with axes
//point4 vertices[8] = {
//    point4(-0.5, -0.5,  0.5, 1.0),
//    point4(-0.5,  0.5,  0.5, 1.0),
//    point4(0.5,  0.5,  0.5, 1.0),
//    point4(0.5, -0.5,  0.5, 1.0),
//    point4(-0.5, -0.5, -0.5, 1.0),
//    point4(-0.5,  0.5, -0.5, 1.0),
//    point4(0.5,  0.5, -0.5, 1.0),
//    point4(0.5, -0.5, -0.5, 1.0)
//};
//
//// RGBA colors
//color4 vertex_colors[8] = {
//    color4(0.0, 0.0, 0.0, 1.0),  // black
//    color4(1.0, 0.0, 0.0, 1.0),  // red
//    color4(1.0, 1.0, 0.0, 1.0),  // yellow
//    color4(0.0, 1.0, 0.0, 1.0),  // green
//    color4(0.0, 0.0, 1.0, 1.0),  // blue
//    color4(1.0, 0.0, 1.0, 1.0),  // magenta
//    color4(1.0, 1.0, 1.0, 1.0),  // white
//    color4(0.0, 1.0, 1.0, 1.0)   // cyan
//};
//
//int Index = 0;
//void quad(int a, int b, int c, int d) {
//    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
//    colors[Index] = vertex_colors[b]; points[Index] = vertices[b]; Index++;
//    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
//    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
//    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
//    colors[Index] = vertex_colors[d]; points[Index] = vertices[d]; Index++;
//}
//
//// generate 12 triangles: 36 vertices and 36 colors
//void colorcube() {
//    quad(1, 0, 3, 2);
//    quad(2, 3, 7, 6);
//    quad(3, 0, 4, 7);
//    quad(6, 5, 1, 2);
//    quad(4, 5, 6, 7);
//    quad(5, 4, 0, 1);
//}
//
//GLuint  model_view;  // model-view matrix uniform shader variable location
//GLuint  projection; // projection matrix uniform shader variable location
//
//Camera* camera;
//CameraMode viewMode = SIDE;
//float camTime = 0.0f;
//bool isCamMoving = false;
//
//void init() {
//    colorcube();
//
//    // Load shaders and use the resulting shader program
//    Shader* shader = new Shader("mvp.vert", "main.frag");
//    GLuint program = shader->program;
//    glUseProgram(program);
//
//    // Create a vertex array object
//    GLuint vao;
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//
//    // Create and initialize a buffer object
//    GLuint buffer;
//    glGenBuffers(1, &buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, buffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);
//
//    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
//    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
//
//    // set up vertex arrays
//    GLuint vPosition = glGetAttribLocation(program, "vPosition");
//    glEnableVertexAttribArray(vPosition);
//    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//    GLuint vColor = glGetAttribLocation(program, "vColor");
//    glEnableVertexAttribArray(vColor);
//    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(points)));
//
//    model_view = glGetUniformLocation(program, "model_view");
//    projection = glGetUniformLocation(program, "projection");
//    camera = new Camera();
//
//    glEnable(GL_DEPTH_TEST);
//    glClearColor(1.0, 1.0, 1.0, 1.0);
//}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    mat4 mv = camera->getViewMatrix();
//    mat4 pv = camera->getProjectionMatrix();
//    mat4 sc = scale(mat4(1.0f), vec3(500, 500, 500));
//    mv = mv * sc;
//
//    glUniformMatrix4fv(model_view, 1, GL_FALSE, &mv[0][0]);
//    glUniformMatrix4fv(projection, 1, GL_FALSE, &pv[0][0]);
//    
//    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
//    glutSwapBuffers();
//}
//
//void keyboard(unsigned char key, int x, int y) {
//    switch (key) {
//    case 033: // Escape Key
//    case 'q': case 'Q':
//        exit(EXIT_SUCCESS);
//        break;
//    case '1':
//        viewMode = FRONT;
//        isCamMoving = true;
//        break;
//    case '2':
//        viewMode = SIDE;
//        isCamMoving = true;
//        break;
//    case '3':
//        viewMode = ORTHO;
//        isCamMoving = true;
//        break;
//    }
//}
//
//void idle() {
//    if (isCamMoving) {
//        camTime += 0.0005;
//
//        if (camTime >= 1) {
//            camera->setCameraMode(viewMode);
//            camTime = 0;
//            isCamMoving = false;
//        }
//        camera->changeEyePos(viewMode, camTime);
//        camera->changeProjection(viewMode, camTime);
//
//        glutPostRedisplay();
//    }
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
//    glutInitWindowSize(1000, 500);
//    glutCreateWindow("Color Cube");
//    glewInit();
//
//    init();
//
//    glutDisplayFunc(display);
//    glutKeyboardFunc(keyboard);
//    glutIdleFunc(idle);
//
//    glutMainLoop();
//    return 0;
//}

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
	glewInit();

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
