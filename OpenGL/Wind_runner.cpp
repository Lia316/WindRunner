#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

using namespace std;
using namespace glm;

typedef vec4  color4;
typedef vec4  point4;
const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

point4 points[NumVertices];
color4 colors[NumVertices];

// Vertices of a unit cube centered at origin, sides aligned with axes
point4 vertices[8] = {
    point4(-0.5, -0.5,  0.5, 1.0),
    point4(-0.5,  0.5,  0.5, 1.0),
    point4(0.5,  0.5,  0.5, 1.0),
    point4(0.5, -0.5,  0.5, 1.0),
    point4(-0.5, -0.5, -0.5, 1.0),
    point4(-0.5,  0.5, -0.5, 1.0),
    point4(0.5,  0.5, -0.5, 1.0),
    point4(0.5, -0.5, -0.5, 1.0)
};

// RGBA colors
color4 vertex_colors[8] = {
    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(1.0, 0.0, 0.0, 1.0),  // red
    color4(1.0, 1.0, 0.0, 1.0),  // yellow
    color4(0.0, 1.0, 0.0, 1.0),  // green
    color4(0.0, 0.0, 1.0, 1.0),  // blue
    color4(1.0, 0.0, 1.0, 1.0),  // magenta
    color4(1.0, 1.0, 1.0, 1.0),  // white
    color4(0.0, 1.0, 1.0, 1.0)   // cyan
};

// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int Axis = Xaxis;
GLfloat Theta[NumAxes] = { 0.0, 0.0, 0.0 };
GLuint theta;  // The location of the "theta" shader uniform variable

// quad generates two triangles for each face and assigns colors  to the vertices

int Index = 0;

void quad(int a, int b, int c, int d) {
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[b]; points[Index] = vertices[b]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[d]; points[Index] = vertices[d]; Index++;
}

// generate 12 triangles: 36 vertices and 36 colors
void colorcube() {
    quad(1, 0, 3, 2);
    quad(2, 3, 7, 6);
    quad(3, 0, 4, 7);
    quad(6, 5, 1, 2);
    quad(4, 5, 6, 7);
    quad(5, 4, 0, 1);
}

void init() {
    colorcube();

    // Load shaders and use the resulting shader program
    Shader* shader = new Shader("main.vert", "main.frag");
    GLuint program = shader->program;
    glUseProgram(program);

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(points)));

    theta = glGetUniformLocation(program, "theta");

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniform3fv(theta, 1, Theta);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 033: // Escape Key
    case 'q': case 'Q':
        exit(EXIT_SUCCESS);
        break;
    }
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        switch (button) {
        case GLUT_LEFT_BUTTON:    Axis = Xaxis;  break;
        case GLUT_MIDDLE_BUTTON:  Axis = Yaxis;  break;
        case GLUT_RIGHT_BUTTON:   Axis = Zaxis;  break;
        }
    }
}

void idle() {
    Theta[Axis] += 0.01;
    if (Theta[Axis] > 360.0) {
        Theta[Axis] -= 360.0;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Color Cube");
    glewInit();

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}

//#include <windows.h>
//#include <gl/gl.h>
//#include <gl/glut.h>
//#include "GameManager.h"
//
//GameManager* gameManager;
//
//void init();
//void draw();
//void moveTimer(int time);
//void fireTimer(int time);
//void starTimer(int time);
//void groundTimer(int time);
//void mushTimer(int time);
//void keyboard(unsigned char key, int x, int y);
//
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	init();
//
//	glutDisplayFunc(draw);
//
//	glutTimerFunc(10, moveTimer, 0);
//	glutTimerFunc(FIRETIME, fireTimer, 0);
//	glutTimerFunc(STARTIME, starTimer, 0);
//	glutTimerFunc(GROUNDTIME, groundTimer, 0);
//	glutTimerFunc(GROUNDTIME * 5, mushTimer, 0);
//	glutKeyboardFunc(keyboard);
//
//	glutMainLoop();
//	return 0;
//}
//
//void init(void) {
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	glutInitWindowSize(1000, 500);
//	glutInitWindowPosition(900, 0);
//	glutCreateWindow("Wind Runner");
//	glClearColor(0.0, 0.0, 0.0, 0.0);
//	glShadeModel(GL_FLAT);
//
//	gameManager = new GameManager();
//}
//
//void draw() {
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gameManager->viewProjectionMode();
//
//	glClearColor(0.5, 0.5, 0.5, 0.0);
//
//	glEnable(GL_DEPTH_TEST);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gameManager->viewLookMode();
//	
//	gameManager->draw();
//	glutSwapBuffers();
//}
//
//void moveTimer(int time) {
//	gameManager->move(moveTimer);
//	gameManager->characterAnimation(moveTimer);
//}
//
//void fireTimer(int time) {
//	gameManager->firemaker(fireTimer);
//}
//
//void starTimer(int time) {
//	gameManager->starmaker(starTimer);
//}
//
//void groundTimer(int time) {
//	gameManager->groundmaker(groundTimer);
//}
//
//void mushTimer(int time) {
//	gameManager->mushmaker(mushTimer);
//}
//
//void keyboard(unsigned char key, int x, int y) {
//	gameManager->keyboard(key, x, y);
//}
