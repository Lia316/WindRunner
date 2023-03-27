#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include "math.h"
#include "Character.h"

#define KEY_FRAME_NUM 5
#define JOINT_NUM 8

Character::Character()
    : Entity(glutGet(GLUT_WINDOW_WIDTH) / 10, glutGet(GLUT_WINDOW_HEIGHT) / 4, 30, 50, 0) {
	jumpSpeed = 14;
    lowjumpSpeed = 10;
	jumpState = false;

	upArmAngleL = 0.0f;
	upArmAngleR = 0.0f;
	lowArmAngleL = 0.0f;
	lowArmAngleR = 0.0f;
	upLegAngleL = 0.0f;
	upLegAngleR = 0.0f;
	lowLegAngleL = 0.0f;
	lowLegAngleR = 0.0f;
	
	time = 0;
	currentKeyFrame = 0;
}

void Character::draw() {
    glPushMatrix();
        // to world coordinate
        glTranslatef(x, y, 0);
        glScalef(7, 3, 7);
        // to make character stand up at model coordinate origin
        glTranslatef(2, 0, 0);
        glRotatef(90, 0, 1, 0);
        glTranslatef(0, 8, 0);
   
	    drawHead();
	    drawTorso();
	    drawLeftArm();
	    drawRightArm();
	    drawPelvis();
    glPopMatrix();
}

void Character::jump() {
	y += speed;
	if(jumpState == true)
		speed = speed - 0.4;
}

void Character::setjump() {
	if (!jumpState) {//점프중이 아닐 때,
		speed = jumpSpeed;
		jumpState = true;
	}
}

void Character::setlowjump() {
    if (!jumpState) {//점프중이 아닐 때,
        speed = lowjumpSpeed;
        jumpState = true;
    }
}

void Character::setfall() {
    jumpState = true;
}

void Character::stop(Entity* ground) {
    speed = 0;
    jumpState = false;
    y = ground->getHeight();
}

void Character::sink() {
	y -= 10;
}

bool Character::isJumping() {
    return this->jumpState;
}

float Character::getPositionX() {
    return x;
}

float Character::getPositionY() {
    return y;
}

float* Character::interpolateKeyframes(double& time)
{
	float* angles = new float[JOINT_NUM];
	int currentKeyFrame = 0;
	while (time > keyFrameTimes[currentKeyFrame + 1])
	{
		currentKeyFrame++;
	}
	int nextKeyFrame = (currentKeyFrame + 1) % KEY_FRAME_NUM;
	float t = (time - keyFrameTimes[currentKeyFrame]) / fabs(keyFrameTimes[nextKeyFrame] - keyFrameTimes[currentKeyFrame]);

	for (int i = 0; i < JOINT_NUM; i++) {
		angles[i] = keyFrameAngles[currentKeyFrame][i] + t * (keyFrameAngles[nextKeyFrame][i] - keyFrameAngles[currentKeyFrame][i]);
	}
	return angles;
}

void Character::animation(void(*t)(int))
{
	time += 0.1;
	time = fmod(time, keyFrameTimes[KEY_FRAME_NUM - 1]);
	float* angles = interpolateKeyframes(time);

	upArmAngleL = angles[0];
	upArmAngleR = angles[1];
	lowArmAngleL = angles[2];
	lowArmAngleR = angles[3];
	upLegAngleL = angles[4];
	upLegAngleR = angles[5];
	lowLegAngleL = angles[6];
	lowLegAngleR = angles[7];

	glutPostRedisplay();
}

void Character::drawHead()
{
    glPushMatrix();
        // neck
        glColor3f(1, 0, 0);
        glTranslatef(0, 4.5, 0);
        glutSolidCube(1);
        // head
        glPushMatrix();
            glColor3f(0, 0, 1);
            glTranslatef(0, 1.5, 0);
            glScalef(2, 1.5, 1);
            glutSolidSphere(1, 18, 18);
        glPopMatrix();
    glPopMatrix() ;
}

void Character::drawTorso()
{
    glPushMatrix();
        glColor3f(0, 0, 1);
        glTranslatef(0, 2, 0);
        glScalef(3, 4, 2);
        glutSolidCube(1);
    glPopMatrix();
}

void Character::drawLeftArm()
{ 
    glPushMatrix();
        glColor3f(0, 1, 0);

        // Transform
        glTranslatef(0.0, 4.0, 0.0);
        glRotatef(upArmAngleL, 1, 0, 0); // arm animation

        // Modeling
        glTranslatef(-2, -1.5, 0);

        // upper arm
        glPushMatrix();
            glScalef (1, 3, 1);
            glutSolidCube(1.0);
        glPopMatrix();
        // lower arm
        glPushMatrix();
            glTranslatef(0.0, -1.5, 0.0);
            glRotatef(lowArmAngleL, 1, 0, 0); // arm animation
            glTranslatef(0.0, -1.5, 0.0);
             // hand
            glPushMatrix();
                glColor3f(0, 0, 0);
                glTranslatef(0.0, -2, 0.0);
                glutSolidSphere(0.5, 18, 18);
            glPopMatrix();
            glColor3f(0, 1, 0);
            glScalef (1, 3, 1);
            glutSolidCube(1.0);
        glPopMatrix();

    glPopMatrix();
}

void Character::drawRightArm()
{ 
    glPushMatrix();
        glColor3f(0, 1, 0);

        // Transform
        glTranslatef(0.0, 4.0, 0.0);
        glRotatef(upArmAngleR, 1, 0, 0); // arm animation

        // Modeling
        glTranslatef(2, -1.5, 0);

        // upper arm
        glPushMatrix();
            glScalef (1, 3, 1);
            glutSolidCube(1.0);
        glPopMatrix();
        // lower arm
        glPushMatrix();
            glTranslatef(0.0, -1.5, 0.0);
            glRotatef(lowArmAngleR, 1, 0, 0); // arm animation
            glTranslatef(0.0, -1.5, 0.0);
             // hand
            glPushMatrix();
                glColor3f(0, 0, 0);
                glTranslatef(0.0, -2, 0.0);
                glutSolidSphere(0.5, 18, 18);
            glPopMatrix();
            glColor3f(0, 1, 0);
            glScalef (1, 3, 1);
            glutSolidCube(1.0);
        glPopMatrix();

    glPopMatrix();
}

void Character::drawPelvis()
{
    glPushMatrix();
        glColor3f(0, 0, 1);
        glTranslatef(0, -0.5, 0);
        glutSolidCube(1);
        
        drawLeftLeg();
        drawRightLeg();
    glPopMatrix();
}

void Character::drawLeftLeg()
{
    glPushMatrix();
        glColor3f(0, 1, 1);

        // Transform
        glRotatef(upLegAngleL, 1, 0, 0); // leg animation

        // Modeling
        // upper leg
        glTranslatef(-1, -2.0, 0);
        glPushMatrix();
            glScalef(1, 4, 1);
            glutSolidCube(1);
        glPopMatrix();
        // lower leg
        glPushMatrix();
            glTranslatef(0, -2.0, 0);
            glRotatef(lowLegAngleL, 1, 0, 0); // leg animation
            glTranslatef(0, -1.5, 0);
            // foot
            glPushMatrix();
                glTranslatef(0.0, -2.0, 0.5);
                glScalef(1, 1, 2.0);
                glColor3f(0, 0, 0);
                glutSolidCube(1);
            glPopMatrix();
            glColor3f(0, 1, 1);
            glScalef(1, 3, 1);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
}

void Character::drawRightLeg()
{
    glPushMatrix();
        glColor3f(0, 1, 1);

        // Transform
        glRotatef(upLegAngleR, 1, 0, 0); // leg animation

        // Modeling
        // upper leg
        glTranslatef(1, -2.0, 0);
        glPushMatrix();
            glScalef(1, 4, 1);
            glutSolidCube(1);
        glPopMatrix();
        // lower leg
        glPushMatrix();
            glTranslatef(0, -2.0, 0);
            glRotatef(lowLegAngleR, 1, 0, 0); // leg animation
            glTranslatef(0, -1.5, 0);
            // foot
            glPushMatrix();
                glTranslatef(0.0, -2.0, 0.5);
                glScalef(1, 1, 2.0);
                glColor3f(0, 0, 0);
                glutSolidCube(1);
            glPopMatrix();
            glColor3f(0, 1, 1);
            glScalef(1, 3, 1);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();
}