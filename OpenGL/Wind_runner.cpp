#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>

void init();
void drawGround();
void reshape(int w, int h);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Wind Runner");
	init();
	glutDisplayFunc(drawGround);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

typedef struct rect {
	float x;
	float y;
	float width;
	float height;
} rect;
rect rectangle;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	rectangle.x = 0.;
	rectangle.y = 0;
	rectangle.width = glutGet(GLUT_WINDOW_WIDTH);
	rectangle.height = glutGet(GLUT_WINDOW_HEIGHT)/4;
}

void drawGround()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.7f, 0.5f, 0.3f);
	glBegin(GL_POLYGON);
	glVertex2f(rectangle.x, rectangle.y);
	glVertex2f(rectangle.x + rectangle.width, rectangle.y);
	glVertex2f(rectangle.x + rectangle.width, rectangle.y + rectangle.height);
	glVertex2f(rectangle.x, rectangle.y + rectangle.height);
	glEnd();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	rectangle.width = w;
	rectangle.height = h / 4;
}
